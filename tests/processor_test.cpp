/**
 * @file processor_test.cpp
 * @copyright Copyright 2020 tobanteAudio.
 */

#include "catch2/catch.hpp"

#include "plugin_processor.hpp"

TEST_CASE("processor: Name", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    REQUIRE(processor.getName() == juce::String {"Juce6 Demo"});
}

TEST_CASE("processor: HasEditor", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    REQUIRE(processor.hasEditor() == false);
}

TEST_CASE("processor: AcceptsMidi", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    REQUIRE(processor.acceptsMidi() == false);
}

TEST_CASE("processor: ProducesMidi", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    REQUIRE(processor.producesMidi() == false);
}

TEST_CASE("processor: IsMidiEffect", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    REQUIRE(processor.isMidiEffect() == false);
}

TEST_CASE("processor: BusesLayoutSupportMono", "[demo][processor]")
{
    auto processor     = Juce6DemoProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::mono();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportStereo", "[demo][processor]")
{
    auto processor     = Juce6DemoProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::stereo();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportInvalid", "[demo][processor]")
{
    auto processor     = Juce6DemoProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == false);
}

TEST_CASE("processor: ValueTree", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    auto& vts      = processor.GetAPVTS();
    REQUIRE(&vts.processor == &processor);
}

TEST_CASE("processor: ZeroGainMono", "[demo][processor]")
{
    constexpr auto numChannels = 1;
    constexpr auto numSamples  = 128;

    auto midi   = juce::MidiBuffer {};
    auto buffer = juce::AudioBuffer<float> {numChannels, numSamples};

    // fill buffer with all 1.0
    for (auto i = 0; i < numChannels; i++)
    {
        for (auto j = 0; j < numSamples; j++)
        {
            buffer.setSample(i, j, 1.0f);
        }
    }

    auto processor = Juce6DemoProcessor {};
    processor.GetAPVTS().getRawParameterValue("gain")->store(0.0f);
    processor.prepareToPlay(44'100.0, numSamples);
    processor.processBlock(buffer, midi);

    // buffer should be silent
    for (auto i = 0; i < numChannels; i++)
    {
        for (auto j = 0; j < numSamples; j++)
        {
            auto const sample = buffer.getSample(i, j);
            REQUIRE(sample == 0.0f);
        }
    }
}

TEST_CASE("processor: ZeroGainStereo", "[demo][processor]")
{
    constexpr auto numChannels = 2;
    constexpr auto numSamples  = 64;

    auto midi   = juce::MidiBuffer {};
    auto buffer = juce::AudioBuffer<float> {numChannels, numSamples};

    // fill buffer with all 1.0
    for (auto i = 0; i < numChannels; i++)
    {
        for (auto j = 0; j < numSamples; j++)
        {
            buffer.setSample(i, j, 1.0f);
        }
    }

    auto processor = Juce6DemoProcessor {};
    processor.GetAPVTS().getRawParameterValue("gain")->store(0.0f);
    processor.prepareToPlay(44'100.0, numSamples);
    processor.processBlock(buffer, midi);

    // buffer should be silent
    for (auto i = 0; i < numChannels; i++)
    {
        for (auto j = 0; j < numSamples; j++)
        {
            auto const sample = buffer.getSample(i, j);
            REQUIRE(sample == 0.0f);
        }
    }
}
