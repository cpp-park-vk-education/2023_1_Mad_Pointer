#pragma once
#include "../entity/entity_base.h"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <set>

namespace ecs {
    class EntityManager {
        class EntityContainerBase {
        public:
            virtual ~EntityContainerBase() {}
            virtual std::string getEntityContainerTypeName() const = 0;
            virtual void DestroyEntity(EntityBase* object) = 0;
            virtual EntityBase* getEntity(EntityId) const = 0;
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
                //object->~EntityBase();
                //DestroyObject(object);
            }

            EntityId addEntity(EntityId id, std::shared_ptr<EntityBase> entity) {
                m_entities[id] = entity;
                return entity->getEntityId();
            }

            EntityClassType* getEntity(EntityId id) const override{
                return m_entities.at(id);
            }

            void delEntity(EntityId id) {
                m_entities.erase(id);
            }
        private:
            std::unordered_map<EntityId, std::shared_ptr<EntityBase>> m_entities;
        };

        using EntityTypeId = std::size_t;
        using EntityId = std::size_t;
        using EntityRegistry = std::unordered_map<EntityTypeId, EntityContainerBase*>;
        using PendingDestroyedEntities = std::vector<EntityId>;
        using EntityHandleTable = std::unordered_map<EntityId, EntityContainerBase*>;

    public:
        EntityManager(const EntityManager&) = delete;
        EntityManager& operator=(EntityManager&) = delete;

        template<class EntityClassType>
        inline EntityContainer<EntityClassType>* getEntityContainer() {
            auto componentTypeId = EntityClassType::STATIC_ENTITY_TYPE_ID;
            auto entityContainer = m_entityRegistry.at(componentTypeId);
            return static_cast<EntityClassType*>(entityContainer);
        }

        EntityId acquireEntityId(EntityBase* entity);

        void ReleaseEntityId(EntityId id);

        EntityManager(ComponentManager* componentManagerInstance);
        ~EntityManager();

        template<class EntityClassType, class... Args>
        EntityId CreateEntity(Args&&... args) {
            EntityBase* entity = std::make_shared<EntityClassType>(std::forward<Args>(args)...);
            auto entityContainer = getEntityContainer<EntityClassType>();
            auto entityId = entityContainer->addEntity(entity->getEntityId(), entity);
            m_entityIdToContainerBase[entityId] = entityContainer;
            return entityId;
        }

        void DestroyEntity(EntityId entityId);

        inline EntityBase* getEntity(EntityId entityId) {
            return m_entityIdToContainerBase.at(entityId)->getEntity(entityId);

        }

        void RemoveDestroyedEntities();

    private:
        EntityHandleTable m_entityIdToContainerBase;
        EntityRegistry m_entityRegistry;
        PendingDestroyedEntities m_pendingDestroyedEntities;
        size_t m_numPendingDestroyedEntities;
        ComponentManager* m_componentManagerInstance;

    };
}
