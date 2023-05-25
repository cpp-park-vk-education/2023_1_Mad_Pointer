#pragma once
#include "api.h"
#include "base_component.h"

namespace ecs {
    using ComponentTypeId = size_t;
    template<typename ComponentType>
    class Component : public ComponentBase {
    public:
        ComponentTypeId getStaticComponentTypeId() const {
            return STATIC_COMPONENT_TYPE_ID;
        }

        Component() {}
        virtual ~Component();

        static ComponentTypeId STATIC_COMPONENT_TYPE_ID;
    };
}
