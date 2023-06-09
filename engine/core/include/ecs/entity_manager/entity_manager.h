#pragma once
#include "entity_base.h"
#include "component_manager.h"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <memory>
#include <set>

namespace ecs {
    class EntityManager {
        class EntityContainerBase {
        public:
            virtual ~EntityContainerBase() {}
            virtual std::string getEntityContainerTypeName() const = 0;
            virtual void DestroyEntity(EntityBase* object) = 0;
            virtual EntityBase* getEntity(EntityId) const = 0;
            virtual void delEntity(EntityId) = 0;

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
                return static_cast<EntityClassType*>(m_entities.at(id).get());
            }

            void delEntity(EntityId id) override{
                m_entities.erase(id);
            }
        private:
            std::unordered_map<EntityId, std::shared_ptr<EntityBase>> m_entities;
        };

        using EntityTypeId = std::size_t;
        using EntityId = std::size_t;
        using EntityRegistry = std::unordered_map<EntityTypeId, std::unique_ptr<EntityContainerBase>>;
        using PendingDestroyedEntities = std::vector<EntityId>;
        using EntityHandleTable = std::unordered_map<EntityId, EntityContainerBase*>;
        using EntityLookupTable = std::vector<EntityBase*>;

    public:
        EntityManager(const EntityManager&) = delete;
        EntityManager& operator=(EntityManager&) = delete;

        template<class EntityClassType>
        inline EntityContainer<EntityClassType>* getEntityContainer() {
            //auto entityContainer = m_entityRegistry.at(componentTypeId);
            //return static_cast<EntityContainer<EntityClassType>*>(entityContainer);

            auto entityTypeID = EntityClassType::STATIC_ENTITY_TYPE_ID;

            //EntityContainer<EntityClassType>* entityContainer = nullptr;

            auto iter = m_entityRegistry.find(entityTypeID);
            if (iter == m_entityRegistry.end()) {
                //entityContainer = new EntityContainer<EntityClassType>();
                m_entityRegistry[entityTypeID] = std::make_unique<EntityContainer<EntityClassType>>();
                return static_cast<EntityContainer<EntityClassType>*>(m_entityRegistry[entityTypeID].get());
            }

            //entityContainer = static_cast<EntityContainer<EntityClassType>*>(iter->second.get());
            return static_cast<EntityContainer<EntityClassType>*>(m_entityRegistry[entityTypeID].get());
        }

        EntityId acquireEntityId(EntityBase* entity);

        void ReleaseEntityId(EntityId id);

        EntityManager(ComponentManager* componentManagerInstance);
        ~EntityManager();

        template<class EntityClassType, class... Args>
        EntityId CreateEntity(Args&&... args) {
            std::shared_ptr<EntityBase> entity = std::make_shared<EntityClassType>(std::forward<Args>(args)...);
            auto entityContainer = getEntityContainer<EntityClassType>();

            auto entityId = acquireEntityId(entity.get());
            entity->setEntityId(entityId);
            entityContainer->addEntity(entity->getEntityId(), entity);
            m_entityIdToContainerBase[entityId] = entityContainer;

            entity->onEnable();
            return entityId;
        }

        void DestroyEntity(EntityId entityId);

        inline EntityBase* getEntity(EntityId entityId) {
            try {
                return m_entityIdToContainerBase.at(entityId)->getEntity(entityId);
            } catch (...) {
                return nullptr;
            }

        }

        void RemoveDestroyedEntities();

    private:
        EntityLookupTable m_entityLookupTable;
        EntityHandleTable m_entityIdToContainerBase;
        EntityRegistry m_entityRegistry;
        PendingDestroyedEntities m_pendingDestroyedEntities;
        size_t m_numPendingDestroyedEntities;
        ComponentManager* m_componentManagerInstance;

    };
}
