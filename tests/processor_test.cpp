/**
 * @file processor_test.cpp
 * @copyright Copyright 2020 tobanteAudio.
 */

#include "catch2/catch.hpp"

#include "plugin_processor.hpp"

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

TEST_CASE("processor: APVTS", "[demo][processor]")
{
    auto processor = Juce6DemoProcessor {};
    auto& vts = processor.GetAPVTS();
    REQUIRE(&vts.processor == &processor);
}

