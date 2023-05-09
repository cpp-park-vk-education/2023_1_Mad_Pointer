#include "../component_manager/component_manager.h"

namespace ecs {
    class EntityBase {
        using EntityTypeId = size_t;
    public:
        EntityBase();
        virtual ~EntityBase();

        template<typename ComponentType>
        ComponentType* getComponent() const {
            return m_componentManagerInstance->getComponent<ComponentType>(m_entityId);
        }

        template <typename ComponentType, typename ...Args>
        ComponentType* addComponent(Args&&... args) {
            return m_componentManagerInstance->addComponent<ComponentType>(m_enityId, std::forward<>(args...));
        }

        template<typename ComponentType>
        ComponentType* removeComponent() const {
            return m_componentManagerInstance->removeComponent<ComponentType>(m_entityId);
        }

        virtual EntityTypeId getStaticEntityTypeId() const = 0;

        inline EntityId getEntityId() const {
            return m_entityId;
        }

        void setActive(bool active) {
            m_isActive = active;
        }

        inline bool isActive() const {
            return m_isActive;
        }

        virtual void onEnable() {}
        virtual void onDisable() {}
    protected:
        EntityId m_entityId; // создаем при инициализации инстанса entity base'a;
        bool m_isActive = true;
    private:
        ComponentManager* m_componentManagerInstance;

    };
}
