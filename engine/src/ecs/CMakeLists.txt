set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(EngineECSCoreStaticLib)

set(ENGINE_DIR ../../)

include_directories(${ENGINE_DIR}include/ecs)

include_directories(${ENGINE_DIR}include/ecs/component_manager)

include_directories(${ENGINE_DIR}include/ecs/component)
include_directories(${ENGINE_DIR}include/ecs/entity)

include_directories(${ENGINE_DIR}include/ecs/entity_manager)

include_directories(${ENGINE_DIR}include/ecs/system)

include_directories(${ENGINE_DIR}include/ecs/system_manager)

set(SOURCE_FILES_ENGINE_ECS_CORE
        component/component_base.cpp
        component_manager/component_manager.cpp
        entity/entity_base.cpp
        entity_manager/entity_manager.cpp
        system/system_base.cpp
        system_registry/system_registry.cpp
        ../utils/family_type_id.cpp
        )

#add_executable(EngineECSCoreStaticLib ${SOURCE_FILES_ENGINE_ECS_CORE})
add_library(EngineECSCoreStaticLib STATIC ${SOURCE_FILES_ENGINE_ECS_CORE})
#add_executable(EngineECSCore ${HEADER_FILES} ${SOURCE_FILES} )
