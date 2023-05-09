#include "../event/event_delegate.h"
#include "../event/event_handler.h"

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
        friend class event::EventBase;
        friend class EntityManager;

    public:
        Engine();
        ~Engine();

            inline EntityManager* GetEntityManager() { return m_entityManager; }

            inline ComponentManager* GetComponentManager() { return m_componentManager; }

            inline SystemManager* GetSystemManager() { return m_systemManager; }

            template<class E, class... Args>
            void sendEvent(Args&&... eventArgs)  {
                m_eventHandler->Send<E>(std::forward<Args>(eventArgs)...);
            }

            void update(float tickMs);

    private:
        utils::Timer* m_engineTime;
        EntityManager* m_entityManager;
        ComponentManager* m_componentManager;
        SystemManager* m_systemManager;
        event::EventHandler* m_eventHandler;

        Engine(const Engine&) = delete;
        Engine& operator=(Engine&) = delete;

        template<class EventType>
        inline void subscribeEvent(event::internal::EventBaseDelegate* const eventDelegate) {
            m_eventHandler->AddEventCallback<EventType>(eventDelegate);
        }

        inline void unsubscribeEvent(event::internal::EventBaseDelegate* eventDelegate);
    };
}
