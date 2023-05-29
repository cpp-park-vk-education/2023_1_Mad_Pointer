#pragma once
#include "base_component.h"

namespace ecs {
    using ComponentTypeId = size_t;
    template<typename ComponentType>
    class Component : public ComponentBase {
    public:
        ComponentTypeId getStaticComponentTypeId() const {
            return STATIC_COMPONENT_TYPE_ID;
        }

        Component() = default;
        ~Component() override;

        const static ComponentTypeId STATIC_COMPONENT_TYPE_ID;
    };

    template<typename ComponentType>
    Component<ComponentType>::~Component() = default;

}
template<class ComponentType>
const ecs::ComponentTypeId ecs::Component<ComponentType>::STATIC_COMPONENT_TYPE_ID = ecs::utils::internal::FamilyTypeId<ComponentBase>::get<ComponentType>();

