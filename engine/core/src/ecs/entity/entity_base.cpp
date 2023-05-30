#include "entity_base.h"

namespace ecs {
    EntityBase::EntityBase(ComponentManager* instance) : m_componentManagerInstance(instance), m_isActive(true) {}

    EntityBase::~EntityBase() {}

    void EntityBase::setActive(bool active) {
        if (m_isActive == active) {
            return;
        }
        m_isActive = active;
        if (m_isActive) {
            onEnable();
            return;
        }
        onDisable();
        return;
    }
}