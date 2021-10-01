/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class RotarySlider : public juce :: Slider{
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    juce::Label nameLabel;
public:
    RotarySlider(SineWaveSynthesizerAudioProcessor& audioProcessor, char* name);
    RotarySlider() {};
    void resized() override;
};




class SineWaveSynthesizerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SineWaveSynthesizerAudioProcessorEditor(SineWaveSynthesizerAudioProcessor&);
    ~SineWaveSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SineWaveSynthesizerAudioProcessor& audioProcessor;

    std::vector<juce::Component*> main,adsrTime,adsrVel;

    juce::Label debugLabel;
    juce::ComboBox waveFormComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SineWaveSynthesizerAudioProcessorEditor)
};
