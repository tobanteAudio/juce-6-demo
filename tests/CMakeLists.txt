project(tests)

add_executable(${PROJECT_NAME} main_test.cpp processor_test.cpp)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Juce6DemoPlugin
        tobanteAudio::CompilerWarnings
        tobanteAudio::CompilerOptions
        tobanteAudio::CodeCoverage
        Catch2::Catch2
)

catch_discover_tests(${PROJECT_NAME})