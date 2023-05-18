cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)
add_subdirectory(src/ecs)

include_directories(include/game_loop)

add_library(EngineStaticLib STATIC src/game_loop/game_loop.cpp src/engine/engine.cpp include/game_loop/game_loop.h)