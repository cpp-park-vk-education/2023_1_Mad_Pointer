#include "../../../include/ecs/component/base_component.h"

namespace ecs {

    ComponentBase::ComponentBase() : m_owner(INVALID_ENTITY_ID), m_enabled(true) {}
    ComponentBase::~ComponentBase() {}
}
