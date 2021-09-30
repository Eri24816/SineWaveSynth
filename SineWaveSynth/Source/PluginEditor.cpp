/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

SineWaveSynthesizerAudioProcessorEditor::SineWaveSynthesizerAudioProcessorEditor(SineWaveSynthesizerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), RotarySliders()
{ 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    RotarySliders.push_back(new RotarySlider(audioProcessor, "level"));
    setSize(400, 300);
    
    
    //RotarySliders[0] = new RotarySlider(audioProcessor, "aTime");
    /*
    RotarySliders.push_back(RotarySlider(audioProcessor, "dTime"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "sTime"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "rTime"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "aVel"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "dVel"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "sVel"));
    RotarySliders.push_back(RotarySlider(audioProcessor, "rVel"));*/
    for (auto &it : RotarySliders) {
        addAndMakeVisible(it->slider);
    }
    
}

SineWaveSynthesizerAudioProcessorEditor::~SineWaveSynthesizerAudioProcessorEditor()
{
    for (auto& it : RotarySliders) {
        delete it;
    }
}

//==============================================================================
void SineWaveSynthesizerAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    /*
    g.setColour(juce::Colours::white);
    int x = 50;
    int y = 200;
    int width = 50;
    int height = levelSlider.getHeight();

    g.drawFittedText("Level", levelSlider.getBounds().getX(), y, width, height, juce::Justification::centred, 1);*/

}

void SineWaveSynthesizerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 2;
    int sliderHeight = area.getHeight() / 4;
    int x = 100;
    int y = 100;

    
    for (auto& it : RotarySliders) {
        it->slider.setBounds(x, y, sliderWidth, sliderHeight);
    }
    /*
    juce::FlexBox fb;                                               
    fb.flexWrap = juce::FlexBox::Wrap::wrap;                        
    fb.justifyContent = juce::FlexBox::JustifyContent::center;      
    fb.alignContent = juce::FlexBox::AlignContent::center;          
    
    for (auto& it : RotarySliders) {
        fb.items.add(juce::FlexItem(it->slider).withMinWidth(50.0f).withMinHeight(50.0f));;
    }
    fb.performLayout(area.toFloat());*/
}