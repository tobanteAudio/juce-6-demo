cmake_minimum_required(VERSION 3.15)

project(tobanteAudioJuce6Demo VERSION 0.1.0)

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

add_subdirectory(3rd_party/JUCE)
#add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
# juce_set_vst2_sdk_path(...)
# juce_set_aax_sdk_path(...)

set_directory_properties(PROPERTIES JUCE_COMPANY_COPYRIGHT "Copyright @ tobanteAudio")
set_directory_properties(PROPERTIES JUCE_COMPANY_NAME "tobanteAudio")
set_directory_properties(PROPERTIES JUCE_COMPANY_WEBSITE "https://github.com/tobanteAudio")
set_directory_properties(PROPERTIES JUCE_COMPANY_EMAIL "tobanteAudio@gmail.com")

juce_add_plugin(CMakePluginExample
    PRODUCT_NAME "Juce6 Demo"               # The name of the final executable, which can differ from the target name
    FORMATS AU VST3 Standalone              # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    IS_SYNTH FALSE                          # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                  # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                 # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                    # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE       # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD FALSE           # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE toAu           # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE J6dm                        # A unique four-character plugin id with at least one upper-case character
)

target_sources(CMakePluginExample PRIVATE
    plugin/plugin_editor.cpp
    plugin/plugin_processor.cpp
)

target_include_directories(CMakePluginExample PUBLIC plugin)
target_compile_definitions(CMakePluginExample
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

# juce_add_binary_data(AudioPluginData SOURCES ...)
target_link_libraries(CMakePluginExample PRIVATE
    # AudioPluginData
    juce::juce_audio_utils
    juce::juce_dsp
)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
enable_testing()
add_subdirectory(3rd_party/Catch2 ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/Catch2 EXCLUDE_FROM_ALL)
include(CTest)
include(Catch)

set (tcc_test_source tests/main_test.cpp tests/processor_test.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${tcc_test_source})
add_executable(test_demo ${tcc_test_source})
target_include_directories(test_demo PRIVATE ${CMAKE_SOURCE_DIR}/3rd_party/JUCE/modules)
target_link_libraries(test_demo
        PRIVATE
        CMakePluginExample
        Catch2::Catch2
)


include(CTest)
include(Catch)
catch_discover_tests(test_demo)