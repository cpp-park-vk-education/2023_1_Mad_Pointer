set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(TheFloors)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)

include_directories(engine/game_loop/include)
include_directories(game/shooter_game/include)
include_directories(game/cars_game/include)

add_executable(TheFloors game/main.cpp)

target_include_directories(TheFloorsGame PUBLIC ${INCLUDE_DIRS})
target_link_libraries(TheFloors PUBLIC EngineStaticLib)
