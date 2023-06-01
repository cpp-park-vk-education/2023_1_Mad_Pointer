set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(TheFloorsGame)


include_directories(shooter_game/include)

set(SOURCE_GAME_FILES main.cpp)

add_executable(TheFloorsGame ${SOURCE_GAME_FILES})
set(INCLUDE_DIRS shooter_game/include)

target_link_libraries(TheFloorsGame PUBLIC EngineStaticLib)
target_include_directories(TheFloorsGame PUBLIC ${INCLUDE_DIRS})
