/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RotarySlider::RotarySlider(SineWaveSynthesizerAudioProcessor& audioProcessor, char* varName):nameLabel("nameLabel",varName) {
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

    setTextBoxStyle(juce::Slider::TextBoxBelow,
        true,
        getTextBoxWidth(),
        getTextBoxHeight());
    setTextValueSuffix("s");

    setRotaryParameters(-2.5 + 6.283, 2.5 + 6.283, true);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


    attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, varName,*this));
    //setValue(0.1);

    nameLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(nameLabel);
    
};

void RotarySlider::resized() {
    juce::Slider::resized();
    //setBounds();
    nameLabel.setBounds(getLocalBounds().getProportion(juce::Rectangle<float>(0,.8, 1, .2)));
}



SineWaveSynthesizerAudioProcessorEditor::SineWaveSynthesizerAudioProcessorEditor(SineWaveSynthesizerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), rotarySliders()
{ 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    rotarySliders.insert(rotarySliders.end(),{ new RotarySlider(audioProcessor, "level"),
        new RotarySlider(audioProcessor, "aTime"),
        new RotarySlider(audioProcessor, "dTime"), 
        new RotarySlider(audioProcessor, "sTime"), 
        new RotarySlider(audioProcessor, "rTime"), 
        new RotarySlider(audioProcessor, "aVel"), 
        new RotarySlider(audioProcessor, "dVel"), 
        new RotarySlider(audioProcessor, "sVel"), 
        new RotarySlider(audioProcessor, "rVel"), });
    
    
    for (auto &it : rotarySliders) {
        addAndMakeVisible(it);
    }
    setSize(400, 300);

}

SineWaveSynthesizerAudioProcessorEditor::~SineWaveSynthesizerAudioProcessorEditor()
{
    for (auto& it : rotarySliders) {
        delete it;
    }
}

//==============================================================================
void SineWaveSynthesizerAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
    g.setColour(juce::Colours::white);

    g.drawFittedText("Level", getBounds().getProportion(juce::Rectangle<float>(0, 0, 1, 0.2)), juce::Justification::centred, 1);


}

void SineWaveSynthesizerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 2;
    int sliderHeight = area.getHeight() / 4;
    int x = 100;
    int y = 100;

    /*
    for (auto& it : RotarySliders) {
        it->slider.setBounds(x, y, sliderWidth, sliderHeight);
    }
    */
    juce::FlexBox fb;                                               
    fb.flexWrap = juce::FlexBox::Wrap::wrap;                        
    fb.justifyContent = juce::FlexBox::JustifyContent::center;      
    fb.alignContent = juce::FlexBox::AlignContent::center;          
    
    for (auto& it : rotarySliders) {
        fb.items.add(juce::FlexItem(*it).withMinWidth(70.0f).withMinHeight(90.0f));;
    }
    fb.performLayout(area.toFloat());
}