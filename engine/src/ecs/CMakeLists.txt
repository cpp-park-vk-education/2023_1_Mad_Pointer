set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(EngineECSCore)

set(HEADER_FILES_ENGINE_ECS_CORE
        ../../include/ecs/component/component.h
        ../../include/ecs/component/base_component.h
        ../../include/ecs/component_manager/component_manager.h
        ../../include/ecs/entity/entity.h
        ../../include/ecs/entity/entity_base.h
        ../../include/ecs/entity_manager/entity_manager.h
        ../../include/ecs/system/system.h
        ../../include/ecs/system/system_base.h
        ../../include/ecs/system_manager/system_manager.h

        )

set(SOURCE_FILES_ENGINE_ECS_CORE
        component/component_base.cpp
        component_manager/component_manager.cpp
        entity/entity_base.cpp
        entity_manager/entity_manager.cpp
        system/system_base.cpp
        system_registry/system_registry.cpp
        )

#add_executable(EngineECSCore ${HEADER_FILES} ${SOURCE_FILES} )
