#pragma once
#include "component_manager.h"
#include <iostream>
namespace ecs {

    using EntityTypeId = size_t;
    using EntityId = size_t;

    class EntityBase {
        friend class EntityManager;
        ComponentManager* m_componentManagerInstance;
    public:

        EntityBase(ComponentManager* instance);
        virtual ~EntityBase();

        template<typename ComponentType>
        ComponentType* getComponent() const;

        template <typename ComponentType, typename ...Args>
        ComponentType* addComponent(Args&&... args);

        template<typename ComponentType>
        ComponentType* removeComponent() const {
            return m_componentManagerInstance->removeComponent<ComponentType>(m_entityId);
        }

        virtual EntityTypeId getStaticEntityTypeId() const = 0;

        inline EntityId getEntityId() const {
            return m_entityId;
        }

        void setActive(bool active);

        inline bool isActive() const {
            return m_isActive;
        }

        void setEntityId(ecs::EntityId id) {
            m_entityId = id;
        }

        virtual void onEnable() {}
        virtual void onDisable() {}
    protected:
        EntityId m_entityId;
        bool m_isActive = true;
    };
}

template <typename ComponentType, typename ...Args>
ComponentType* ecs::EntityBase::addComponent(Args&&... args) {
    return m_componentManagerInstance->addComponent<ComponentType>(m_entityId, std::forward<Args>(args)...);
}

template<typename ComponentType>
ComponentType *ecs::EntityBase::getComponent() const  {
    return m_componentManagerInstance->getComponent<ComponentType>(m_entityId);
}
