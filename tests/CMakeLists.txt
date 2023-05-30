cmake_minimum_required(VERSION 3.8)

project(Tests)
set(CMAKE_CXX_STANDARD 20)

set(ENGINE_TEST_SOURCES
        engine/utils/test_timer.cpp)
add_executable(EngineTests ${ENGINE_TEST_SOURCES})
target_link_libraries(EngineTests GTest::gtest_main EngineStaticLib)
add_test(NAME EngineTests COMMAND EngineTests)
