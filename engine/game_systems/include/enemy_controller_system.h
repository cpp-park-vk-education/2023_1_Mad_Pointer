#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include <cmath>

#define PI 3.14159265

class EnemyControllerSystem : public ecs::System<EnemyControllerSystem>, public ecs::event::EventListenerBase {
public:
    explicit EnemyControllerSystem(ecs::Engine* engine) : m_engine(engine), m_playerTransform(nullptr), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~EnemyControllerSystem() override { unregisterEventCallbacks(); }

    void preUpdate(float dt) override {
        for (auto& movable : m_movable) {
            if (m_killedObjs.count(movable.getEID())) {
                movable.setActive(false);
            }
        }
        m_killedObjs.clear();
    }

    void update(float dt) override {
        for (auto& movable : m_movable) {
            if (movable) {
                movable.getTransform()->setSpeed(1);

                sf::Vector2f point1 = movable.getTransform()->getPosition();
                sf::Vector2f point2 = m_playerTransform->getPosition();

                float angleCos = pow(point2.x - point1.x, 2) / (std::abs(point2.x - point1.x) * sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)));
                float angle = std::acos(angleCos);
                //if (angle == 0) angle = 0.01;
                angle = angle * 180 / 3.1415;

                if (point2.x <= point1.x && point2.y <= point1.y) {

                }
                if (point2.x <= point1.x && point2.y <= point1.y) {
                    movable.getTransform()->setAngle(180 + angle);
                } else if (point2.x >= point1.x && point2.y <= point1.y) {
                    movable.getTransform()->setAngle(360 - angle);
                } else if (point2.x <= point1.x && point2.y >= point1.y) {
                    movable.getTransform()->setAngle(180 - angle);
                } else {
                    movable.getTransform()->setAngle(angle);
                }
            }
        }
    }

    struct Movable {
    public:

        Movable(ecs::EntityBase* entity, TransformComponent* transform, float offset) : m_entity(entity),
                                                                                        m_entityId(entity->getEntityId()),
                                                                                        m_transformComponent(transform),
                                                                                        m_offset(offset) {}

        ~Movable() = default;

        TransformComponent* getTransform() {
            return m_transformComponent;
        }

        void setActive(bool active) {
            m_isActive = active;
        }

        explicit operator bool() const {
            if (m_entity) {
                return m_isActive;
            }
            return false;
        }

        ecs::EntityId getEID () const {
            return m_entityId;
        }

        float getOffset() {
            return m_offset;
        }

    private:
        ecs::EntityId m_entityId;
        bool m_isActive = true;
        ecs::EntityBase* m_entity;
        TransformComponent* m_transformComponent;
        float m_offset;
    };

private:
    void registerEventCallbacks() {
        registerEventCallback(&EnemyControllerSystem::onGameObjectCreated);
        registerEventCallback(&EnemyControllerSystem::onGameObjectDestroyed);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        m_killedObjs.insert(event->m_EntityID);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        static int firstRegistry= 0;
        if (firstRegistry) {
            CollisionComponent* component = m_engine->getComponentManager()->getComponent<CollisionComponent>(event->m_EntityID);
            if (component->getCollisionType() == CollisionType::ProjectileCollisionType) {
                return;
            }
            auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);

            if (!entity) {
                return;
            }

            auto transform = entity->getComponent<TransformComponent>();
            registerMovable(entity, transform, event->m_offset);
            return;
        }
        ++firstRegistry;
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        m_playerTransform = entity->getComponent<TransformComponent>();
    }

    void registerMovable(ecs::EntityBase* entity, TransformComponent* transform, float offset) {
        m_movable.emplace_back(entity, transform, offset);
    }

    void onWallCreated(const WallCreated* event) {
        m_minBounds = event->m_minBounds;
        m_maxBounds = event->m_maxBounds;
    }

    void onWallDestroyed(const WallDestroyed* event) {}

    void unregisterEventCallbacks() {
        unregisterEventCallback(&EnemyControllerSystem::onGameObjectCreated);
        unregisterEventCallback(&EnemyControllerSystem::onGameObjectDestroyed);
    }

private:
    TransformComponent* m_playerTransform;
    ecs::Engine* m_engine;
    std::set<ecs::EntityId> m_killedObjs;
    std::vector<Movable> m_movable;
    sf::Vector2f m_minBounds;
    sf::Vector2f m_maxBounds;
};
