#include "base_component.h"

namespace ecs {
    const size_t INVALID_ENTITY_ID = -1;
    ComponentBase::ComponentBase() : m_owner(INVALID_ENTITY_ID), m_enabled(true) {}
    ComponentBase::~ComponentBase() {}
}
