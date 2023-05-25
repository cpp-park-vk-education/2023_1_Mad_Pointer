cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

find_package(SFML COMPONENTS system window graphics)

set(SOURCE_FILES_ENGINE
        src/game_loop/game_loop.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})
target_link_libraries(EngineStaticLib EngineECSCoreStaticLib sfml-system sfml-graphics sfml-window)
# target_link_libraries(EngineStaticLib PRIVATE sfml-system sfml-graphics sfml-window)

set(INCLUDE_DIRS
        include/game_loop
        include/game_systems)

target_include_directories(EngineStaticLib PUBLIC ${INCLUDE_DIRS})
