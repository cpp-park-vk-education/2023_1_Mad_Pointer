#pragma once
#include "entity_base.h"
#include "family_type_id.h"
#include <numeric>

namespace ecs {
    size_t INVALID_ENTITY_ID = -1;
    template<class EntityClass>
    class Entity : public EntityBase {
    public:
        //void operator delete(void*) = delete;
        //void operator delete[](void*) = delete;

        static const EntityTypeId STATIC_ENTITY_TYPE_ID;
        virtual EntityTypeId getStaticEntityTypeId() const override { return STATIC_ENTITY_TYPE_ID; }

        Entity(ComponentManager* instance): EntityBase(instance) {}

        virtual ~Entity() {}
    };

    template<class EntityClass>
    const EntityTypeId Entity<EntityClass>::STATIC_ENTITY_TYPE_ID = ecs::utils::internal::FamilyTypeId<EntityBase>::get<EntityClass>();
}
