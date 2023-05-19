set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(EngineECSCoreStaticLib)

#include ecs
include_directories(include/ecs)
include_directories(include/ecs/component_manager)
include_directories(include/ecs/component)
include_directories(include/ecs/entity)
include_directories(include/ecs/entity_manager)
include_directories(include/ecs/system)
include_directories(include/ecs/system_manager)

#include events
include_directories(include/event)

#include utils
include_directories(include/utils)

set(SOURCE_FILES_ENGINE_ECS_CORE
        src/ecs/component/component_base.cpp
        src/ecs/component_manager/component_manager.cpp
        src/ecs/entity/entity_base.cpp
        src/ecs/entity_manager/entity_manager.cpp
        src/ecs/system/system_base.cpp
        src/ecs/system_registry/system_registry.cpp
        src/utils/family_type_id.cpp
        )

#add_executable(EngineECSCoreStaticLib ${SOURCE_FILES_ENGINE_ECS_CORE})
add_library(EngineECSCoreStaticLib STATIC ${SOURCE_FILES_ENGINE_ECS_CORE})
#add_executable(EngineECSCore ${HEADER_FILES} ${SOURCE_FILES} )