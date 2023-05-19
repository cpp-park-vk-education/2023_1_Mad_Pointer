#include "engine.h"
#include "event_handler.h"
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"

#include "timer.h"

namespace ecs {
    Engine::Engine() :
    m_engineTime(std::make_unique<utils::Timer>()),
    m_eventHandler(std::make_unique<event::EventHandler>()),
    m_systemManager(std::make_unique<SystemManager>()),
    m_componentManager(std::make_unique<ComponentManager>()),
    m_entityManager(std::make_unique<EntityManager>(m_componentManager.get())) {}

    Engine::~Engine() {}

    void Engine::update(float deltaTime) {
        m_engineTime->Tick(deltaTime);

        m_systemManager->Update(deltaTime);
        m_eventHandler->DispatchEvents();

        m_entityManager->RemoveDestroyedEntities();
        m_eventHandler->DispatchEvents();
    }

    void Engine::unsubscribeEvent(event::internal::EventBaseDelegate* eventDelegate) {
        m_eventHandler->RemoveEventCallback(eventDelegate);
    }

} // namespace ecs