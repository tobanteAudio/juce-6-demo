cmake_minimum_required(VERSION 3.15)

project(CMAKE_PLUGIN_EXAMPLE VERSION 0.1.0)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")
    set(CMAKE_CXX_STANDARD_REQUIRED YES)
    set(CMAKE_CXX_EXTENSIONS NO)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    # set(BUILD_SHARED_LIBS OFF)

    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()

    if(MSVC)
        CHECK_CXX_COMPILER_FLAG("/arch:AVX2" COMPILER_OPT_ARCH_AVX2_SUPPORTED)
        if(COMPILER_OPT_ARCH_AVX2_SUPPORTED)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
        endif()
        CHECK_CXX_COMPILER_FLAG("/MP" COMPILER_OPT_MP_BUILD_SUPPORTED)
        if(COMPILER_OPT_MP_BUILD_SUPPORTED)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        endif()
    endif()

    include(CheckIPOSupported)
    check_ipo_supported(RESULT TOBANTEAUDIO_BUILD_LTO)
    if(TOBANTEAUDIO_BUILD_LTO)
        message(STATUS "tobanteAudio: LTO is available.")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()

add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
# juce_set_vst2_sdk_path(...)
# juce_set_aax_sdk_path(...)

juce_add_plugin(CMakePluginExample
    # VERSION ...                           # Set this if the plugin version is different to the project version
    # ICON_BIG ...                          # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "tobanteAudio"             # Specify the name of the plugin's author
    IS_SYNTH FALSE                          # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                  # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                 # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                    # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE       # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD FALSE            # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Juce           # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                        # A unique four-character plugin id with at least one upper-case character
    FORMATS AU VST3 Standalone              # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "Audio Plugin Example"     # The name of the final executable, which can differ from the target name
)

# if(TOBANTEAUDIO_BUILD_LTO)
#     message(STATUS "tobanteAudio: LTO is enabled for CMakePluginExample.")
#     set_property(TARGET CMakePluginExample PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#     # set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# endif()

# `target_sources` adds source files to a target. We pass the target that needs the sources as the
# first argument, then a visibility parameter for the sources (PRIVATE is normally best practice,
# although it doesn't really affect executable targets). Finally, we supply a list of source files
# that will be built into the target. This is a standard CMake command.

target_sources(CMakePluginExample PRIVATE
    plugin/plugin_editor.cpp
    plugin/plugin_processor.cpp
)

target_compile_definitions(CMakePluginExample
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(AudioPluginData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

# juce_add_modules(${CMAKE_SOURCE_DIR}/3rd_party/JUCE/modules/juce_dsp)

target_link_libraries(CMakePluginExample PRIVATE
    # AudioPluginData
    juce::juce_audio_utils
    juce::juce_dsp
)
