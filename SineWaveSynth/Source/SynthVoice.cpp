/*
  ==============================================================================
    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da
  ==============================================================================
*/

#include "SynthVoice.h"

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
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    sustain = false;
    if (allowTailOff)
    {
        
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
        float value = std::sin(currentAngle) * level * tailOff;
        outputBuffer.addSample(0, i, value);
        outputBuffer.addSample(1, i, value);

        currentAngle += angleIncrement;
        if (sustain)
            tailOff *= 0.9999;
        else
            tailOff *= 0.998;

    }

}

void SynthVoice::setLevel(float newLevel)
{
    level = newLevel;
}