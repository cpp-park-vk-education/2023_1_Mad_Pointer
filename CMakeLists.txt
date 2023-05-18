set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.8)
project(TheFloors)

set(HEADER_FILES engine/include/ecs/component/component.h
        engine/include/ecs/component/base_component.h
        engine/include/ecs/component_manager/component_manager.h
        engine/include/ecs/entity/entity.h
        engine/include/ecs/entity/entity_base.h
        engine/include/ecs/entity_manager/entity_manager.h
        engine/include/ecs/system/system.h
        engine/include/ecs/system/system_base.h
        engine/include/ecs/system_manager/system_manager.h
        engine/include/event/event.h
        engine/include/event/event_base.h
        engine/include/event/event_base_dispatcher.h
        engine/include/event/event_delegate.h
        engine/include/event/event_dispatcher.h
        engine/include/event/event_handler.h
        engine/include/event/event_listener.h
        engine/include/memory/allocator/allocator_base.h
        engine/include/memory/allocator/pool_allocator.h
        engine/include/memory/allocator/linear_allocator.h
        engine/include/memory/allocator/stack_allocator.h
        engine/include/memory/chunk_allocator.h
        engine/include/memory/memory_manager.h
        engine/include/utils/family_type_id.h
        engine/include/camera/camera.h
        engine/include/camera/game_camera.h
        engine/include/camera/orthogonal_camera.h
        engine/include/camera/table_top_camera.h
        engine/include/controller/AI_controller.h
        engine/include/controller/controller.h
        engine/include/controller/controller_base.h
        engine/include/controller/player_controller.h
        engine/include/game_systems/collision_system.h
        engine/include/game_systems/controller_system.h
        engine/include/game_systems/input_system.h
        engine/include/game_systems/lifetime_system.h
        engine/include/game_systems/physics_system.h
        engine/include/game_systems/spawn_system.h
        engine/include/game_systems/world_system.h
        engine/include/game_objects_spawn/point_spawn.h
        engine/include/game_objects_spawn/spawn.h
        engine/include/game_objects_spawn/spawn_base.h
        engine/include/game_components/collision_component.h
        engine/include/game_components/respawn_component.h
        engine/include/game_components/rigidbody_component.h
        engine/include/game_components/shape_component.h
        engine/include/game_components/spawn_component.h
        engine/include/game_components/transform.h
        engine/include/game_components/transform_component.h
        engine/include/shape_common/shape.h
        engine/include/shape_common/shape_buffer_index.h
        engine/src/game_loop/game_loop.cpp
)

add_executable(TheFloors ${HEADER_FILES})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -lpthread -lm")

#set(BOOST_ROOT /usr/include/boost)
#include_directories(/usr/include/boost)
#include_directories(/usr/include/openssl)

#set(OPENSSL_USE_STATIC_LIBS TRUE)
#find_package(OpenSSL REQUIRED)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Boost REQUIRED COMPONENTS system thread)
#find_package(Threads REQUIRED)



#add_executable(server_websocket game/server/main.cpp)

#target_link_libraries(client_websocket PRIVATE OpenSSL::SSL OpenSSL::Crypto Boost::system Threads::Threads )
#target_link_libraries(server_websocket PRIVATE OpenSSL::SSL OpenSSL::Crypto Boost::system Threads::Threads )


#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

#add_subdirectory(lib/math)

#add_executable(Test game/client/main.cpp)
#target_link_libraries(Test ${SDL2_LIBRARIES} math)
