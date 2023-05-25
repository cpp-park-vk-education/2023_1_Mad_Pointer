#pragma once

const int ENTITY_LUT_GROW = 1024;
const int ENTITY_T_CHUNK_SIZE = 512;

const int COMPONENT_LUT_GROW = 1024;
const int COMPONENT_T_CHUNK_SIZE = 512;

namespace ecs {
    namespace Event {
        class EventHandler;
    }
    class EntityManager;
    class SystemManager;
    class ComponentManager;

    class Engine;
} // namespace ecs
