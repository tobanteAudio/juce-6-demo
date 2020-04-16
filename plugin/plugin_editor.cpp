#include "plugin_editor.hpp"
#include "plugin_processor.hpp"

Juce6DemoProcessorEditor::Juce6DemoProcessorEditor(Juce6DemoProcessor& p) : AudioProcessorEditor(&p), processorRef(p)
{
    auto& vts = processorRef.GetAPVTS();

    roomSizeAttachment_ = std::make_unique<SliderAttachment>(vts, "room_size", roomSize_);
    addAndMakeVisible(roomSizeLabel_);
    addAndMakeVisible(roomSize_);

    dampingAttachment_ = std::make_unique<SliderAttachment>(vts, "damping", damping_);
    addAndMakeVisible(dampingLabel_);
    addAndMakeVisible(damping_);

    dryLevelAttachment_ = std::make_unique<SliderAttachment>(vts, "dry_level", dryLevel_);
    addAndMakeVisible(dryLevelLabel_);
    addAndMakeVisible(dryLevel_);

    wetLevelAttachment_ = std::make_unique<SliderAttachment>(vts, "wet_level", wetLevel_);
    addAndMakeVisible(wetLevelLabel_);
    addAndMakeVisible(wetLevel_);

    widthAttachment_ = std::make_unique<SliderAttachment>(vts, "width", width_);
    addAndMakeVisible(widthLabel_);
    addAndMakeVisible(width_);

    gainAttachment_ = std::make_unique<SliderAttachment>(vts, "gain", gain_);
    addAndMakeVisible(gainLabel_);
    addAndMakeVisible(gain_);

    setSize(400, 400);
    setResizable(true, true);
    setResizeLimits(400, 400, 8000, 8000);
}

void Juce6DemoProcessorEditor::paint(juce::Graphics& g)
{
    auto const bgColor = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    g.fillAll(bgColor);
}

void Juce6DemoProcessorEditor::resized()
{
    auto area            = getLocalBounds();
    auto const height    = area.getHeight() / 6;
    auto const labelPerc = 4;

    {
        auto section = area.removeFromTop(height);
        roomSizeLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        roomSize_.setBounds(section);
    }

    {
        auto section = area.removeFromTop(height);
        dampingLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        damping_.setBounds(section);
    }

    {
        auto section = area.removeFromTop(height);
        dryLevelLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        dryLevel_.setBounds(section);
    }

    {
        auto section = area.removeFromTop(height);
        wetLevelLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        wetLevel_.setBounds(section);
    }

    {
        auto section = area.removeFromTop(height);
        widthLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        width_.setBounds(section);
    }

    {
        auto section = area.removeFromTop(height);
        gainLabel_.setBounds(section.removeFromLeft(section.getWidth() / labelPerc));
        gain_.setBounds(section);
    }
}
