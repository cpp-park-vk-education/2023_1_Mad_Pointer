#pragma once
#include "system.h"
#include "entity_base.h"
#include "game_event.h"
#include "event_listener.h"
#include "transform_component.h"
#include "projectile.h"
#include <SFML/Graphics.hpp>

class ScoreSystem : public ecs::System<ScoreSystem>, public ecs::event::EventListenerBase {
public:
    explicit ScoreSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine), m_score(0) {
        registerEventCallbacks();
    }

    ~ScoreSystem() override {
        //unregisterEventCallbacks();
    }

    void postUpdate(float dt) override {}

private:
    void registerEventCallbacks() {
        registerEventCallback(&ScoreSystem::onGameObjectDestroyed);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        m_score += 10;
        std::cout << m_score << std::endl;
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&ScoreSystem::onGameObjectDestroyed);
    }

private:
    ecs::Engine* m_engine;
    int m_score;
};
