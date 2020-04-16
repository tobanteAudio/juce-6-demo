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

    juce::Slider roomSize_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    juce::Slider damping_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    juce::Slider dryLevel_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    juce::Slider wetLevel_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    juce::Slider width_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    juce::Slider gain_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Juce6DemoProcessorEditor)
};
