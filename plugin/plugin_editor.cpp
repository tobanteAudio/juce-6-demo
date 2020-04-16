#include "plugin_editor.hpp"
#include "plugin_processor.hpp"

Juce6DemoProcessorEditor::Juce6DemoProcessorEditor(Juce6DemoProcessor& p) : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    setSize(400, 300);
}

void Juce6DemoProcessorEditor::paint(juce::Graphics& g)
{
    auto const bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    g.fillAll(bgColor);
}

void Juce6DemoProcessorEditor::resized() { }
