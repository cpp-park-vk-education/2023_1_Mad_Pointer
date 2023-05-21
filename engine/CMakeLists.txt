cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

include_directories(include/game_loop)

set(SOURCE_FILES_ENGINE
        src/game_loop/game_loop.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})
target_link_libraries(EngineStaticLib PRIVATE EngineECSCoreStaticLib)
