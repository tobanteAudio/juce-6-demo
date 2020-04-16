#pragma once

#include "plugin_processor.hpp"

class Juce6DemoProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit Juce6DemoProcessorEditor(Juce6DemoProcessor&);
    ~Juce6DemoProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Juce6DemoProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Juce6DemoProcessorEditor)
};
