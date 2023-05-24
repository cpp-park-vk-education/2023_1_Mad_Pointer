cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

find_package(SDL2 REQUIRED)
include_directories(EngineStaticLib ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES_ENGINE
        src/game_loop/game_loop.cpp
        src/game_systems/input_system.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})
target_link_libraries(EngineStaticLib EngineECSCoreStaticLib ${SDL2_LIBRARIES})

set(INCLUDE_DIRS
        include/game_loop
        include/game_systems)

target_include_directories(EngineStaticLib PUBLIC ${INCLUDE_DIRS})
