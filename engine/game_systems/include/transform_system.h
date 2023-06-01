#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include <cmath>

#define PI 3.14159265

class TransformSystem : public ecs::System<TransformSystem>, public ecs::event::EventListenerBase {
public:
    explicit TransformSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~TransformSystem() override {
        //unregisterEventCallbacks();
    }
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
                
                float dx = std::cos((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();
                float dy = std::sin((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();

                if (movable.getTransform()->getPosition().x + dx < m_minBounds.x ||
                    movable.getTransform()->getPosition().x + dx > m_maxBounds.x - movable.getOffset()) {
                    CollisionComponent* component = m_engine->getComponentManager()->getComponent<CollisionComponent>(movable.getEID());
                    if (component->getCollisionType() == CollisionType::ProjectileCollisionType) {
                        m_engine->getEntityManager()->DestroyEntity(movable.getEID());
                    }
                    dx = 0;
                }
                if (movable.getTransform()->getPosition().y + dy < m_minBounds.y ||
                    movable.getTransform()->getPosition().y + dy > m_maxBounds.y - movable.getOffset()) {
                    CollisionComponent* component = m_engine->getComponentManager()->getComponent<CollisionComponent>(movable.getEID());
                    if (component->getCollisionType() == CollisionType::ProjectileCollisionType) {
                        m_engine->getEntityManager()->DestroyEntity(movable.getEID());
                    }
                    dy = 0;
                }
                movable.getTransform()->changePosition(sf::Vector2(dx, dy));
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
        registerEventCallback(&TransformSystem::onBoxCreated);
        registerEventCallback(&TransformSystem::onCarCreated);
        registerEventCallback(&TransformSystem::onGameObjectCreated);
        registerEventCallback(&TransformSystem::onWallCreated);
        registerEventCallback(&TransformSystem::onGameObjectDestroyed);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        m_killedObjs.insert(event->m_EntityID);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform, event->m_offset);
    }

    void onBoxCreated(const BoxCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform, 0);
    }

    void onCarCreated(const CarCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform, event->m_size.x);
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
        unregisterEventCallback(&TransformSystem::onGameObjectCreated);
        registerEventCallback(&TransformSystem::onGameObjectDestroyed);
    }

private:
    ecs::Engine* m_engine;
    std::set<ecs::EntityId> m_killedObjs;
    std::vector<Movable> m_movable;
    sf::Vector2f m_minBounds {0 , 0};
    sf::Vector2f m_maxBounds {1920, 1080};
};
