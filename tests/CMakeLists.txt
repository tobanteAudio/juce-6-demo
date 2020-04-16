project(tests)

set (test_sources main_test.cpp processor_test.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${test_sources})

add_executable(${PROJECT_NAME} ${test_sources})
target_link_libraries(${PROJECT_NAME} PRIVATE
        Juce6DemoPlugin
        tobanteAudio::CompilerWarnings
        tobanteAudio::CompilerOptions
        tobanteAudio::CodeCoverage
        Catch2::Catch2
        )

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG=1)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG=1)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

catch_discover_tests(${PROJECT_NAME})