#pragma once
#include "event_listener.h"

class LifetimeSystem : public ecs::event::EventListenerBase {
    using ActiveLifetimeComponents = std::list<LifetimeComponent*>;
private:

    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

    void OnGameObjectCreated(const GameObjectCreated* event);
    void OnGameObjectDestroyed(const GameObjectDestroyed* event);
    void OnGameObjectSpawned(const GameObjectSpawned* event);
    void OnGameObjectKilled(const GameObjectKilled* event);

    WorldSystem* m_WorldSystem;

    ActiveLifetimeComponents m_ActiveLifetimeComponents;

public:

    LifetimeSystem();
    virtual ~LifetimeSystem();

    void Update(float deltaTime);

    void Reset();

};
