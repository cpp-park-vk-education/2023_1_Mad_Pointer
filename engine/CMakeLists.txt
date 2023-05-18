cmake_minimum_required(VERSION 3.25)
project(engine)
add_subdirectory(src/ecs)

add_executable(engine ${SOURCE_FILES_ENGINE_ECS_CORE})