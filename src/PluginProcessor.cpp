#include "PluginProcessor.h"
#include "PluginEditor.h"

Juce6DemoProcessor::Juce6DemoProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         )
    , undoManager_ {}
    , parameters_ {*this,
                   &undoManager_,
                   "tobanteAudioJuce6Demo",
                   {std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 2.0f, 1.0f)}}
{
}

Juce6DemoProcessor::~Juce6DemoProcessor() {}

const juce::String Juce6DemoProcessor::getName() const { return JucePlugin_Name; }

bool Juce6DemoProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Juce6DemoProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Juce6DemoProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Juce6DemoProcessor::getTailLengthSeconds() const { return 0.0; }

int Juce6DemoProcessor::getNumPrograms()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are
               // 0 programs, so this should be at least 1, even if you're not
               // really implementing programs.
}

int Juce6DemoProcessor::getCurrentProgram() { return 0; }

void Juce6DemoProcessor::setCurrentProgram(int index) { juce::ignoreUnused(index); }

const juce::String Juce6DemoProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void Juce6DemoProcessor::changeProgramName(int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

void Juce6DemoProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void Juce6DemoProcessor::releaseResources() {}

bool Juce6DemoProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) return false;
#endif

    return true;
#endif
}

void Juce6DemoProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

bool Juce6DemoProcessor::hasEditor() const { return false; }

juce::AudioProcessorEditor* Juce6DemoProcessor::createEditor() { return new Juce6DemoProcessorEditor(*this); }

void Juce6DemoProcessor::getStateInformation(juce::MemoryBlock& destData) { juce::ignoreUnused(destData); }

void Juce6DemoProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes);
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new Juce6DemoProcessor(); }
