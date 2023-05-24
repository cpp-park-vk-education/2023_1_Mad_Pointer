#pragma once
#include "entity_manager.h"
#include "event_delegate.h"
#include "event_handler.h"
#include <memory>
#include <utility>

namespace ecs  {
    namespace utils  {
        class Timer;
    }

    class EntityManager;
    class SystemManager;
    class ComponentManager;

    class Engine {
        friend class EntityBase;
        friend class ComponentBase;
        friend class SystemBase;
        friend class EventListenerBase;
        friend class event::EventBase;
        friend class EntityManager;

    public:
        Engine();
        ~Engine();

            inline EntityManager* getEntityManager() { return m_entityManager.get(); }

            inline ComponentManager* getComponentManager() { return m_componentManager.get(); }

            inline SystemManager* getSystemManager() { return m_systemManager.get(); }

            template<class E, class... Args>
            void sendEvent(Args&&... eventArgs)  {
                m_eventHandler->Send<E>(std::forward<Args>(eventArgs)...);
            }

            void update(float tickMs);

            inline void unsubscribeEvent(event::internal::EventBaseDelegate* eventDelegate);

    private:
        std::unique_ptr<utils::Timer> m_engineTime;
        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<ComponentManager> m_componentManager;
        std::unique_ptr<SystemManager> m_systemManager;
        std::unique_ptr<event::EventHandler> m_eventHandler;

        Engine(const Engine&) = delete;
        Engine& operator=(Engine&) = delete;

        template<class EventType>
        inline void subscribeEvent(event::internal::EventBaseDelegate* const eventDelegate) {
            m_eventHandler->AddEventCallback<EventType>(eventDelegate);
        }

    };
}
