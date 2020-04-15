#include "PluginEditor.h"
#include "PluginProcessor.h"

Juce6DemoProcessorEditor::Juce6DemoProcessorEditor(Juce6DemoProcessor& p) : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    setSize(400, 300);
}

Juce6DemoProcessorEditor::~Juce6DemoProcessorEditor() { }

void Juce6DemoProcessorEditor::paint(juce::Graphics& g)
{
    auto const bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    g.fillAll(bgColor);
}

void Juce6DemoProcessorEditor::resized() { }
