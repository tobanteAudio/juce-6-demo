project(plugin)

if(APPLE)
        set(TOBANTEAUDIO_SHOULD_COPY TRUE)
else()
        set(TOBANTEAUDIO_SHOULD_COPY FALSE)
endif(APPLE)

juce_add_plugin(Juce6DemoPlugin
        PRODUCT_NAME "Juce6 Demo"                               # The name of the final executable, which can differ from the target name
        VERSION ${CMAKE_PROJECT_VERSION}                        # Version
        FORMATS AU VST3 Standalone                              # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        IS_SYNTH FALSE                                          # Is this a synth or an effect?
        NEEDS_MIDI_INPUT FALSE                                  # Does the plugin need midi input?
        NEEDS_MIDI_OUTPUT FALSE                                 # Does the plugin need midi output?
        IS_MIDI_EFFECT FALSE                                    # Is this plugin a MIDI effect?
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE                       # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD ${TOBANTEAUDIO_SHOULD_COPY}     # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE toAu                           # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE J6dm                                        # A unique four-character plugin id with at least one upper-case character
)

set(Juce6DemoPlugin_SOURCES 
        plugin_editor.hpp 
        plugin_editor.cpp 
        plugin_processor.hpp
        plugin_processor.cpp
)

target_sources(Juce6DemoPlugin PRIVATE ${Juce6DemoPlugin_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Juce6DemoPlugin_SOURCES})

target_include_directories(Juce6DemoPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Juce6DemoPlugin PUBLIC ${CMAKE_SOURCE_DIR}/3rd_party)
target_include_directories(Juce6DemoPlugin PUBLIC ${CMAKE_SOURCE_DIR}/3rd_party/JUCE/modules)

target_compile_definitions(Juce6DemoPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        )

target_link_libraries(Juce6DemoPlugin PRIVATE
        tobanteAudio::CompilerWarnings
        tobanteAudio::CompilerOptions
        tobanteAudio::CodeCoverage
        juce::juce_audio_utils
        juce::juce_dsp
        ff_meters
        )