/**
 * @file plugin_editor.hpp
 * @copyright Copyright 2020 tobanteAudio.
 */

#pragma once

#include "plugin_processor.hpp"

class Juce6DemoProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit Juce6DemoProcessorEditor(Juce6DemoProcessor&);
    ~Juce6DemoProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

private:
    Juce6DemoProcessor& processorRef;

    foleys::LevelMeterLookAndFeel lnf_;
    foleys::LevelMeter meter_ {foleys::LevelMeter::Minimal};  // See foleys::LevelMeter::MeterFlags for options

    juce::Label roomSizeLabel_ {"room_size", "Room Size"};
    juce::Slider roomSize_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> roomSizeAttachment_;

    juce::Label dampingLabel_ {"damping", "Damping"};
    juce::Slider damping_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> dampingAttachment_;

    juce::Label dryLevelLabel_ {"dryLevel", "Dry Level"};
    juce::Slider dryLevel_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> dryLevelAttachment_;

    juce::Label wetLevelLabel_ {"wetLevel", "Wet Level"};
    juce::Slider wetLevel_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> wetLevelAttachment_;

    juce::Label widthLabel_ {"width", "Width"};
    juce::Slider width_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> widthAttachment_;

    juce::Label gainLabel_ {"gain", "Gain"};
    juce::Slider gain_ {juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight};
    std::unique_ptr<SliderAttachment> gainAttachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Juce6DemoProcessorEditor)
};
