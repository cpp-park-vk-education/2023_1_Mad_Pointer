#pragma once
#include "system.h"
#include "entity_base.h"
#include "game_event.h"
#include "event_listener.h"
#include "collision_component.h"
#include "transform_component.h"
#include "radius_component.h"

#include <cmath>
#include <SFML/Graphics.hpp>

class RectangleCollisionSystem : public ecs::System<RectangleCollisionSystem>, public ecs::event::EventListenerBase {
public:
    explicit RectangleCollisionSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }
    ~RectangleCollisionSystem() override {
        //unregisterEventCallbacks();
    }

    void preUpdate(float dt) override {
        for (auto& rB : m_rigidBodies) {
            if (m_killedObjects.count(rB.getEID())) {
                rB.setActive(false);
            }
        }
        m_killedObjects.clear();
    }

    void update(float dt) override {
        if (m_rigidBodies.size() < 2) { return;}
        for (size_t i = 0; i < m_rigidBodies.size() - 1; ++i) {
            if (!m_rigidBodies[i]) continue;

            for (size_t j = i + 1; j < m_rigidBodies.size(); ++j) {
                if (!m_rigidBodies[j]) continue;

                if (m_rigidBodies[i].checkCollision(m_rigidBodies[j])) {
                    handleCollision(m_rigidBodies[i], m_rigidBodies[j]);
                }
            }
        }
    }
    void postUpdate(float dt) override {
        for (const auto pendToKill : m_pendingToDestroy) {
            m_engine->getEntityManager()->DestroyEntity(pendToKill);
        }
        m_pendingToDestroy.clear();
    }

    struct RigidBody {
    public:
        RigidBody(ecs::EntityBase* entity, TransformComponent* transform, CollisionComponent* collisionComponent, sf::Vector2f size) :
                m_entity(entity),
                m_entityId(entity->getEntityId()),
                m_transformComponent(transform),
                m_collisionComponent(collisionComponent),
                m_size(size) {}

        ~RigidBody() = default;

        bool checkCollision(const RigidBody& other) const {
            float ax1 = m_transformComponent->getPosition().x;
            float ax2 = ax1 + m_size.x;

            float ay1 = m_transformComponent->getPosition().y;
            float ay2 = ay1 + m_size.y;

            float bx1 = other.m_transformComponent->getPosition().x;
            float bx2 = bx1 + other.m_size.x;

            float by1 = other.m_transformComponent->getPosition().y;
            float by2 = by1 + other.m_size.y;

            if (std::max(ax1, ax2) < std::min(bx1, bx2) || std::max(ay1, ay2) < std::min(by1, by2) || std::max(by1, by2) < std::min(ay1, ay2)) {
                return false;
            }
            return true;
        }

        bool operator==(const RigidBody& other) const {
            return m_entity->getEntityId() == other.getEntityId();
        }

        bool operator!=(const RigidBody& other) const {
            return m_entity->getEntityId() != other.getEntityId();
        }

        ecs::EntityId getEntityId() const {
            return m_entity->getEntityId();
        }

        CollisionType getCollisionType() const {
            return m_collisionComponent->getCollisionType();
        };

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

    private:
        ecs::EntityId m_entityId;
        bool m_isActive = true;
        sf::Vector2f m_size;
        ecs::EntityBase* m_entity;
        CollisionComponent*	m_collisionComponent;
        TransformComponent* m_transformComponent;
    };

    using RigidBodyVector = std::vector<RigidBody>;
private:
    void handleCollision(const RigidBody& objectA, const RigidBody& objectB) {
        if (objectA.getCollisionType() == CollisionType::BoxCollisionType && objectB.getCollisionType() == CollisionType::CarCollisionType) {
            m_pendingToDestroy.push_back(objectB.getEntityId());
        } else if (objectA.getCollisionType() == CollisionType::CarCollisionType && objectB.getCollisionType() == CollisionType::BoxCollisionType) {
            m_pendingToDestroy.push_back(objectA.getEntityId());
        } else {}
    }

    [[maybe_unused]] void registerEventCallbacks() {
        registerEventCallback(&RectangleCollisionSystem::onCarCreated);
        registerEventCallback(&RectangleCollisionSystem::onCarDestroyed);
        registerEventCallback(&RectangleCollisionSystem::onBoxCreated);
        registerEventCallback(&RectangleCollisionSystem::onBoxDestroyed);
    }

    void onCarCreated(const CarCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();
        auto collision = entity->getComponent<CollisionComponent>();

        registerRigidBody(entity, transform, collision, event->m_size);
    }

    void onBoxCreated(const BoxCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();
        auto collision = entity->getComponent<CollisionComponent>();

        registerRigidBody(entity, transform, collision, event->m_size);
    }

    void onCarDestroyed(const CarDestroyed* event) {
        unregisterRigidBody(event->m_EntityID);
    }

    void onBoxDestroyed(const BoxDestroyed* event) {
        unregisterRigidBody(event->m_EntityID);
    }

    [[maybe_unused]] void unregisterEventCallbacks() {
        unregisterEventCallback(&RectangleCollisionSystem::onCarCreated);
        unregisterEventCallback(&RectangleCollisionSystem::onCarDestroyed);
        unregisterEventCallback(&RectangleCollisionSystem::onBoxCreated);
        unregisterEventCallback(&RectangleCollisionSystem::onBoxDestroyed);
    }

    void registerRigidBody(ecs::EntityBase* entity, TransformComponent* transform, CollisionComponent* collisionComponent, sf::Vector2f size) {
        m_rigidBodies.emplace_back(entity, transform, collisionComponent, size);
    }

    void unregisterRigidBody(ecs::EntityId gameObjectId) {
        m_killedObjects.insert(gameObjectId);
    }

    ecs::Engine* m_engine;
    RigidBodyVector m_rigidBodies;
    std::unordered_set<ecs::EntityId> m_killedObjects;
    std::vector<ecs::EntityId> m_pendingToDestroy;
};
