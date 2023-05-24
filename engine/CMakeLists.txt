cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

include_directories(game_loop/include)

set(SOURCE_FILES_ENGINE
        game_loop/src/game_loop.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(EngineStaticLib PUBLIC EngineECSCoreStaticLib ${SDL2_LIBRARIES})

set(INCLUDE_DIRS
        include/game_loop)

target_include_directories(EngineStaticLib PUBLIC ${INCLUDE_DIRS})
