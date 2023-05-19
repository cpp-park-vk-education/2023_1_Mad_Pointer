#include "../../../include/ecs/component_manager/component_manager.h"
namespace ecs {
    const int ENTITY_LUT_GROW = 1024;
    const int INVALID_COMPONENT_ID = -1;
    const int COMPONENT_LUT_GROW = 1024;
ComponentManager::ComponentManager() {
    // log here initialize component manager

    const size_t NUMBER_COMPONENTS {utils::internal::FamilyTypeId<ComponentBase>::get()};
    m_EntityComponentMap.resize(ENTITY_LUT_GROW);
    for (auto i = 0; i < ENTITY_LUT_GROW; ++i) {
        m_EntityComponentMap[i].resize(NUMBER_COMPONENTS, INVALID_COMPONENT_ID);
    }
}

ComponentManager::~ComponentManager() {
    for (auto componentContainer : m_ComponentContainerRegistry) {
        delete componentContainer.second;
        componentContainer.second = nullptr;
    }
}

ComponentId ComponentManager::acquireComponentId(ecs::ComponentBase* component) {
    int i = 0;
    for (; i < m_ComponentLUT.size(); ++i) {
        if (!m_ComponentLUT.at(i)) {
            m_ComponentLUT[i] = component;
            return i;
        }
    }
    m_ComponentLUT.resize(m_ComponentLUT.size() + COMPONENT_LUT_GROW, nullptr);
    m_ComponentLUT[i] = component;
    return i;
}

void ComponentManager::releaseComponentId(ecs::ComponentManager::ComponentId id) {
    m_ComponentLUT[id] = nullptr;
}

void ComponentManager::mapEntityComponent(ecs::EntityId entityId, ecs::ComponentManager::ComponentId componentId,
                                              ecs::ComponentManager::ComponentTypeId componentTypeId) {
    static const size_t NUM_COMPONENTS {utils::internal::FamilyTypeId<ComponentBase>::get()};
    if (m_EntityComponentMap.size() - 1 < entityId) {
        size_t oldSize = m_EntityComponentMap.size();
        size_t newSize = oldSize + ENTITY_LUT_GROW;
        m_EntityComponentMap.resize(newSize);

        for (auto i = oldSize; i < newSize; ++i) {
            m_EntityComponentMap[i].resize(NUM_COMPONENTS, INVALID_COMPONENT_ID);
        }
    }
    m_EntityComponentMap[entityId][componentTypeId] = componentId;
    }
}

void ecs::ComponentManager::unmapEntityComponent(ecs::EntityId entityId, ecs::ComponentManager::ComponentId componentId,
                                                 ecs::ComponentManager::ComponentTypeId componentTypeId) {
    m_EntityComponentMap[entityId][componentTypeId] = INVALID_COMPONENT_ID;
    releaseComponentId(componentId);
}
