#include "PluginEditor.h"
#include "PluginProcessor.h"

Juce6DemoProcessorEditor::Juce6DemoProcessorEditor(Juce6DemoProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    setSize(400, 300);
}

Juce6DemoProcessorEditor::~Juce6DemoProcessorEditor() { }

void Juce6DemoProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(),
                     juce::Justification::centred, 1);
}

void Juce6DemoProcessorEditor::resized() { }
