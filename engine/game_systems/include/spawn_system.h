#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include "enemy.h"

#include <cmath>
#include <random>

class SpawnSystem : public ecs::System<SpawnSystem>, public ecs::event::EventListenerBase {
public:
    explicit SpawnSystem(ecs::Engine* engine) : m_engine(engine), m_playerTransform(nullptr), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~SpawnSystem() override {
       // unregisterEventCallbacks();
    }

    void update(float dt) override {
        static int enemiesCount = 0;
        currTime += dt;
        if (currTime > 2000.0) {
            currTime = 0;
            ++enemiesCount;

            std::random_device random_device;
            std::mt19937 generator(random_device());

            std::uniform_real_distribution<> distributionForX(m_minBounds.x + 50, m_maxBounds.x - 50);
            std::uniform_real_distribution<> distributionForY(m_minBounds.y + 50, m_maxBounds.y - 50);

            float x = distributionForX(generator);
            float y = distributionForY(generator);
            for (size_t i = 0; i < enemiesCount; ++i) {
                while(sqrt(pow(m_playerTransform->getPosition().x - x, 2) + pow(m_playerTransform->getPosition().y - y, 2)) < 200) {
                    x = distributionForX(generator);
                    y = distributionForY(generator);
                }

                //while(abs(m_playerTransform->getPosition().y - y) < 200) {
                //}

                m_engine->getEntityManager()->CreateEntity<Enemy>(m_engine, m_engine->getComponentManager(), sf::Vector2f(x, y));
                x = distributionForX(generator);
                y = distributionForY(generator);
            }
        }
    }

private:
    void registerEventCallbacks() {
        registerEventCallback(&SpawnSystem::onGameObjectCreated);
        registerEventCallback(&SpawnSystem::onWallCreated);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        if (m_playerTransform) return;
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        m_playerTransform = entity->getComponent<TransformComponent>();
    }

    void onWallCreated(const WallCreated* event) {
        m_minBounds = event->m_minBounds;
        m_maxBounds = event->m_maxBounds;
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&SpawnSystem::onGameObjectCreated);
        registerEventCallback(&SpawnSystem::onWallCreated);
    }

private:
    float currTime = 0;
    ecs::Engine* m_engine;
    TransformComponent* m_playerTransform;
    sf::Vector2f m_minBounds;
    sf::Vector2f m_maxBounds;
};
