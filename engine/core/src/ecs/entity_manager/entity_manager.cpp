#include "entity_manager.h"

namespace ecs {
    EntityManager::EntityManager(ecs::ComponentManager* componentManagerInstance) : m_componentManagerInstance(componentManagerInstance),
    m_numPendingDestroyedEntities(0), m_entityLookupTable(1024, nullptr) {
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

    EntityId EntityManager::acquireEntityId(ecs::EntityBase *entity) {
        int i = 0;
        for (; i < m_entityLookupTable.size(); ++i) {
            if (!m_entityLookupTable.at(i)) {
                m_entityLookupTable[i] = entity;
                return i;
            }
        }
        m_entityLookupTable.resize(m_entityLookupTable.size() + 1024, nullptr);
        m_entityLookupTable[i] = entity;
        return i;
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
