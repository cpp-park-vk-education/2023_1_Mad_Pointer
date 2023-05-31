#pragma once
#include "system.h"
#include "entity_base.h"
#include "game_event.h"
#include "event_listener.h"
#include "transform_component.h"
#include "projectile.h"
#include <SFML/Graphics.hpp>

class ShootSystem : public ecs::System<ShootSystem>, public ecs::event::EventListenerBase {
public:
    explicit ShootSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }
    ~ShootSystem() override { unregisterEventCallbacks(); }

    void preUpdate(float dt) override {}
    void update(float dt) override {}
    void postUpdate(float dt) override {}

private:
    void registerEventCallbacks() {
        registerEventCallback(&ShootSystem::onLeftMouseButtonClick);
    }

    void onLeftMouseButtonClick(const LeftMouseButtonPressedWithPos* event) {
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&ShootSystem::onLeftMouseButtonClick);
    }
private:
    ecs::Engine* m_engine;
};
