#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void renderNextBlock(juce::AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override;

    void setParams(juce::AudioProcessorValueTreeState* tree);

private:
    float level;
    float frequency;
    int noteMidiNumber;
    float angleIncrement;
    float tailOff;
    bool sustain;
    float aTime, dTime, sDecay, rDecay, aVel, dVel, sVel, rVel;
    int waveform;
    float timeStep;

    enum EnvelopePhase { A, D, S, R } envelopePhase;
    float timeInEnvPhase;
    float intensity;
    float currentAngle;
};