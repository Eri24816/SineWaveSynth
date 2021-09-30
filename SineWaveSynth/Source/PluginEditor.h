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
class RotarySlider {
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
public:
    RotarySlider(SineWaveSynthesizerAudioProcessor& audioProcessor, char* name);
    RotarySlider() {};
    juce::Slider slider;
};

RotarySlider::RotarySlider(SineWaveSynthesizerAudioProcessor& audioProcessor, char* varName) {
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

    slider.setTextBoxStyle(juce::Slider::TextBoxLeft,
        true,
        slider.getTextBoxWidth(),
        slider.getTextBoxHeight());

    slider.setRotaryParameters(-2.5 + 6.283, 2.5 + 6.283, true);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


    attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, varName, slider));
    slider.setValue(0.1);
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

    std::vector<RotarySlider*> RotarySliders;
    //RotarySlider *RotarySliders[8];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SineWaveSynthesizerAudioProcessorEditor)
};
