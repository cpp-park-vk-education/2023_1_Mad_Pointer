#include "../../../include/ecs/entity/entity_base.h"

namespace ecs {
    EntityBase::EntityBase() : m_isActive(true) {}

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