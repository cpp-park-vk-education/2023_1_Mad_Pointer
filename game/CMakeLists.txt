set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(TheFloorsGame)

set(SOURCE_GAME_FILES main.cpp)

add_executable(TheFloorsGame ${SOURCE_GAME_FILES})

target_link_libraries(TheFloorsGame PUBLIC EngineStaticLib)
