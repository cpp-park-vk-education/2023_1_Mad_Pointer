cmake_minimum_required(VERSION 3.25)
project(EngineStaticLib)

add_subdirectory(core)

include_directories(game_loop/include)
include_directories(game_systems/include)
include_directories(game_components/include)
include_directories(game_events)
include_directories(game_objects/game_object/include)
include_directories(game_objects/player/include)
include_directories(game_objects/enemy/include)
include_directories(game_objects/wall/include)
include_directories(game_objects/projectile/include)

set(SOURCE_FILES_ENGINE game_loop/src/game_loop.cpp game_objects/player/src/player.cpp)

add_library(EngineStaticLib STATIC ${SOURCE_FILES_ENGINE})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(EngineStaticLib PUBLIC EngineECSCoreStaticLib sfml-graphics)

set(INCLUDE_DIRS game_loop/include
        game_systems/include
        game_objects/player/include
        game_objects/wall/include
        game_events
        game_components/include
        game_objects/enemy/include
        game_objects/game_object/include
        game_objects/projectile/include
        game_objects/car/include)

target_include_directories(EngineStaticLib PUBLIC ${INCLUDE_DIRS})
