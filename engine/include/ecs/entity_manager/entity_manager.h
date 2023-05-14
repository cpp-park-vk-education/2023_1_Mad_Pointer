#include <string>
#include "../entity/entity_base.h"
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace ecs {
    class EntityManager {
        class EntityContainerBase {
        public:
            virtual ~EntityContainerBase() {}

            virtual std::string getEntityContainerTypeName() const = 0;

            virtual void DestroyEntity(EntityBase* object) = 0;

        };

        template<typename EntityClassType>
        class EntityContainer : public EntityContainerBase {
        public:
            EntityContainer(const EntityContainer&) = delete;
            EntityContainer &operator=(EntityContainer &) = delete;

            EntityContainer() {}

            virtual ~EntityContainer() {}

            virtual std::string getEntityContainerTypeName() const override {
                static std::string ENTITY_TYPE_NAME{typeid(EntityClassType).name()};
                return ENTITY_TYPE_NAME;
            }

            virtual void DestroyEntity(EntityBase* object) override {
                object->~EntityBase();
                this->DestroyObject(object);
            }
        private:
            // place container here
        };

        using EntityTypeId = std::size_t;
        using EntityId = std::size_t;
        using EntityRegistry = std::unordered_map<EntityTypeId, EntityContainerBase*>;
        using PendingDestroyedEntities = std::vector<EntityId>;
        using EntityHandleTable = ecs::utils::HandleTable<EntityContainerBase, EntityId>;

    public:
        EntityManager(const EntityManager&) = delete;
        EntityManager& operator=(EntityManager&) = delete;

        template<class EntityClassType>
        inline EntityContainer<EntityClassType>* getEntityContainer() { }

        EntityId acquireEntityId(EntityBase* entity);

        void ReleaseEntityId(EntityId id);

        EntityManager(ComponentManager* componentManagerInstance);
        ~EntityManager();

        template<class EntityClassType, class... Args>
        EntityId CreateEntity(Args&&... args) {}

        void DestroyEntity(EntityId entityId) {}

        inline EntityBase* getEntity(EntityId entityId) {
            return m_entityHandleTable[entityId];
        }

        inline EntityId getEntityId(EntityId::valueType index) const {
            return m_entityHandleTable[index];
        }

        void RemoveDestroyedEntities();

    private:


        EntityRegistry m_entityRegistry;
        PendingDestroyedEntities m_pendingDestroyedEntities;
        size_t m_numPendingDestroyedEntities;
        ComponentManager*    m_componentManagerInstance;

    };
}
