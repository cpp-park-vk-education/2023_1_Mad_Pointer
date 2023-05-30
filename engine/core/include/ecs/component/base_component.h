#pragma once
#include <iostream>
namespace ecs {
    using ComponentId = size_t;
    using EntityId = size_t;
    class ComponentBase {
    public:
        ComponentBase();
        virtual ~ComponentBase();

        ComponentId getComponentId() const {
            return m_componentId;
        }

        EntityId getOwner() const {
            return m_owner;
        }

        void setActive(bool state) {
            m_enabled = state;
        }

        bool isActive() const {
            return m_enabled;
        }

        void setOwner(EntityId owner) {
            m_owner = owner;
        }

        void setComponentId(ComponentId id) {m_componentId = id;}
    protected:
        ComponentId m_componentId;
        EntityId m_owner;
        bool m_enabled;
    };
}
