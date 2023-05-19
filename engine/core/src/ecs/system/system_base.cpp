#include "system_base.h"

namespace ecs {
    SystemBase::SystemBase(SystemPriority priority, float updateInterval_ms) :
            m_priority(priority),
            m_updateInterval(updateInterval_ms),
            m_enabled(true) {}

    SystemBase::~SystemBase() {}

} // namespace ecs
