project(tests)

set (test_sources main_test.cpp processor_test.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${test_sources})

add_executable(${PROJECT_NAME} ${test_sources})
target_link_libraries(${PROJECT_NAME} PRIVATE Juce6DemoPlugin Catch2::Catch2)

catch_discover_tests(${PROJECT_NAME})