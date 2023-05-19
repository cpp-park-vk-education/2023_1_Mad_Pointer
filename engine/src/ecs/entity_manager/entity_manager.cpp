#include "../../include/ecs/entity_manager/entity_manager.h"

namespace ecs {
    EntityManager::EntityManager(ecs::ComponentManager* componentManagerInstance) : m_componentManagerInstance(componentManagerInstance),
    m_numPendingDestroyedEntities(0),
    m_pendingDestroyedEntities(1024) {
        // log here initialize entity manager
    }

    EntityManager::~EntityManager() {
        for (auto entityComponent : m_entityRegistry) {
            delete entityComponent.second;
            entityComponent.second = nullptr;
        }
        // log release entity manager
    }

    void EntityManager::ReleaseEntityId(ecs::EntityManager::EntityId id) {
        m_entityIdToContainerBase.erase(id);
    }

    void EntityManager::RemoveDestroyedEntities() {
        for (const auto& entityId : m_pendingDestroyedEntities) {
            auto entityContainer = m_entityIdToContainerBase[entityId];
            entityContainer->delEntity(entityId);
            m_componentManagerInstance->removeAllComponents(entityId);
            ReleaseEntityId(entityId);
        }
        m_pendingDestroyedEntities.clear();
    }
}
