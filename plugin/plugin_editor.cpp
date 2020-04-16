#include "plugin_editor.hpp"
#include "plugin_processor.hpp"

Juce6DemoProcessorEditor::Juce6DemoProcessorEditor(Juce6DemoProcessor& p) : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);
    addAndMakeVisible(roomSize_);
    addAndMakeVisible(damping_);
    addAndMakeVisible(dryLevel_);
    addAndMakeVisible(wetLevel_);
    addAndMakeVisible(width_);
    addAndMakeVisible(gain_);
    setSize(400, 300);
}

void Juce6DemoProcessorEditor::paint(juce::Graphics& g)
{
    auto const bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    g.fillAll(bgColor);
}

void Juce6DemoProcessorEditor::resized()
{
    auto area         = getLocalBounds();
    auto const height = area.getHeight() / 6;
    roomSize_.setBounds(area.removeFromTop(height));
    damping_.setBounds(area.removeFromTop(height));
    dryLevel_.setBounds(area.removeFromTop(height));
    wetLevel_.setBounds(area.removeFromTop(height));
    width_.setBounds(area.removeFromTop(height));
    gain_.setBounds(area.removeFromTop(height));
}
