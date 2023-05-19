#include "../../include/utils/family_type_id.h"

namespace ecs {
    class EntityBase;
    class ComponentBase;
    class SystemBase;

    namespace utils::internal {

        template<> size_t FamilyTypeId<EntityBase>::m_typeCount = 0u;
        template<> size_t FamilyTypeId<ComponentBase>::m_typeCount	= 0u;
        template<> size_t FamilyTypeId<SystemBase>::m_typeCount = 0u;

        template class FamilyTypeId<EntityBase>;
        template class FamilyTypeId<ComponentBase>;
        template class FamilyTypeId<SystemBase>;
    }

} // namespace ecs::utils::internal
