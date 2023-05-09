#include "entity_base.h"
#include "../../utils/family_type_id.h"
namespace ecs {
    template<class EntityClass>
    class Entity : public EntityBase {
        void operator delete(void*) = delete;
        void operator delete[](void*) = delete;

    public:

        static const EntityTypeId STATIC_ENTITY_TYPE_ID;

    public:

        virtual EntityTypeId getStaticEntityTypeId() const override { return STATIC_ENTITY_TYPE_ID; }

        Entity() {}

        virtual ~Entity() {}
    };

    template<class EntityClass>
    const EntityTypeId Entity<EntityClass>::STATIC_ENTITY_TYPE_ID = ecs::utils::internal::FamilyTypeId<EntityBase>::get<EntityClass>();
}