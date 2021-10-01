/*
  ==============================================================================
    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da
  ==============================================================================
*/

#include "SynthVoice.h"
#include<math.h>

#define PI juce::MathConstants<float>::pi
#define TWO_PI juce::MathConstants<float>::twoPi


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    noteMidiNumber = midiNoteNumber;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentAngle = 0.f;
    angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi;
    tailOff = 1.0;
    sustain = true;
    envelopePhase = A;
    timeInEnvPhase = 0;
    timeStep = 1 / getSampleRate();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    sustain = false;
    if (allowTailOff)
    {
        envelopePhase = R;
    }
    else
    {
        clearCurrentNote();
        level = 0;
        currentAngle = 0.f;
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    // handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    // handle midi control change
}

void SynthVoice::renderNextBlock(juce::AudioBuffer <float>& outputBuffer, int startSample, int numSamples)
{

    for (int i = startSample; i < (startSample + numSamples); i++)
    {
        
        switch (envelopePhase)
        {
        case A:
            if (timeInEnvPhase >= aTime) { envelopePhase = D; timeInEnvPhase = 0; }
            else {
                intensity = aVel* (timeInEnvPhase / aTime);  
            }
            break;
        case D:
            if (timeInEnvPhase >= dTime) { envelopePhase = S; timeInEnvPhase = 0; }
            else {
                intensity = aVel - (aVel - dVel) * (timeInEnvPhase / dTime);
            }
            break;
        case S:
            intensity *= sDecay;
            break;
        case R:
            intensity *= rDecay;
            break;
        default:
            break;
        
        }
        float value = 0;
        // sine
        if (waveform == 0)value = std::sin(currentAngle);
        // square
        else if (waveform == 1) value = ((int)(currentAngle / PI)) % 2 ? 1 : -1;
        // tri
        else if (waveform == 2) value = abs(fmod(currentAngle / PI,2)-1)+0.5;
        // saw
        else if (waveform == 3) value = fmod( currentAngle / PI,2) - 1;

        value *= level * intensity;
        outputBuffer.addSample(0, i, value);
        outputBuffer.addSample(1, i, value);

        currentAngle += angleIncrement;
        timeInEnvPhase += timeStep;
       
    }
}

void SynthVoice::setParams(juce::AudioProcessorValueTreeState* tree)
{
    level = tree->getRawParameterValue("level")->load();
    aTime = tree->getRawParameterValue("aTime")->load()+0.002f;
    dTime = tree->getRawParameterValue("dTime")->load()+0.002f;
    float sTime = tree->getRawParameterValue("sTime")->load();
    sDecay = powf(2, -1.0f / (sTime*getSampleRate()));
    float rTime = tree->getRawParameterValue("rTime")->load();
    rDecay = powf(2, -1.0f / (rTime * getSampleRate()));
    aVel = tree->getRawParameterValue("aVel")->load();
    dVel = tree->getRawParameterValue("dVel")->load();
    sVel = tree->getRawParameterValue("sVel")->load();
    rVel = tree->getRawParameterValue("rVel")->load();
    waveform = tree->getParameterAsValue("waveform").getValue();
    //DBG(waveform);
}