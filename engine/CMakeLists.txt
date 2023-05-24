cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

set(SOURCE_FILES_ENGINE
        game_loop/src/game_loop.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})
target_link_libraries(EngineStaticLib PUBLIC EngineECSCoreStaticLib)

set(INCLUDE_DIRS
        include/game_loop)

target_include_directories(EngineStaticLib PUBLIC ${INCLUDE_DIRS})
