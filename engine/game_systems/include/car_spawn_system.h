#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include "box.h"
#include <cmath>
#include <random>

const sf::Vector2f BOX_SIZE(50, 50);

class CarSpawnSystem : public ecs::System<CarSpawnSystem>, public ecs::event::EventListenerBase {
public:
    explicit CarSpawnSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~CarSpawnSystem() override {
        // unregisterEventCallbacks();
    }

    void update(float dt) override {
        static int carsCount = 3;
        currTime += dt;
        if (currTime > 1000.0) {
            currTime = 0;
            m_engine->sendEvent<UpdateScore>();

            std::random_device random_device;
            std::mt19937 generator(random_device());

            std::uniform_real_distribution<> distributionForX(m_minBounds.x + 50, m_maxBounds.x - 50);
            std::uniform_real_distribution<> distributionForY(m_minBounds.y + 50, -50);

            float x = distributionForX(generator);
            float y = distributionForY(generator);
            for (size_t i = 0; i < carsCount; ++i) {
                    x = distributionForX(generator);
                    y = distributionForY(generator);

                m_engine->getEntityManager()->CreateEntity<Box>(m_engine, m_engine->getComponentManager(), sf::Vector2f(x, y), BOX_SIZE);
                x = distributionForX(generator);
                y = distributionForY(generator);
            }
        }
    }

private:
    void registerEventCallbacks() {
        registerEventCallback(&CarSpawnSystem::onGameObjectCreated);
        registerEventCallback(&CarSpawnSystem::onWallCreated);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        //if (m_playerTransform) return;
        //auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        //m_playerTransform = entity->getComponent<TransformComponent>();
    }

    void onWallCreated(const WallCreated* event) {
        m_minBounds = event->m_minBounds;
        m_maxBounds = event->m_maxBounds;
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&CarSpawnSystem::onGameObjectCreated);
        registerEventCallback(&CarSpawnSystem::onWallCreated);
    }

private:
    float currTime = 0;
    ecs::Engine* m_engine;
    sf::Vector2f m_minBounds = {0, -1000};
    sf::Vector2f m_maxBounds = {1920, 2080};
};
