/**
 * @file plugin_processor.hpp
 * @copyright Copyright 2020 tobanteAudio.
 */

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class Juce6DemoProcessor final : public juce::AudioProcessor
{
public:
    Juce6DemoProcessor();
    ~Juce6DemoProcessor() override = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    auto GetAPVTS() -> juce::AudioProcessorValueTreeState& { return parameters_; }

private:
    juce::UndoManager undoManager_;
    juce::AudioProcessorValueTreeState parameters_;

    std::atomic<float>* roomSize_ = nullptr;
    std::atomic<float>* damping_  = nullptr;
    std::atomic<float>* dryLevel_ = nullptr;
    std::atomic<float>* wetLevel_ = nullptr;
    std::atomic<float>* width_    = nullptr;
    juce::dsp::Reverb reverb_;

    std::atomic<float>* gain_ = nullptr;
    juce::dsp::Gain<float> outputGain_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Juce6DemoProcessor)
};
