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

bool isPointInRect(const sf::Vector2f& first, const sf::Vector2f& last, const sf::Vector2f& point) {
    if (point.x >= first.x && point.x <= last.x && point.y >= first.y && point.y <= last.y) {
        return true;
    }
    return false;
}

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
            float ay1 = m_transformComponent->getPosition().y;

            float ax2 = m_transformComponent->getPosition().x + m_size.x;
            float ay2 = m_transformComponent->getPosition().y + m_size.y;

            float bx1 = other.m_transformComponent->getPosition().x;
            float by1 = other.m_transformComponent->getPosition().y;

            float bx2 = other.m_transformComponent->getPosition().x + other.m_size.x;
            float by2 = other.m_transformComponent->getPosition().y;

            float bx3 = other.m_transformComponent->getPosition().x + other.m_size.x;
            float by3 = other.m_transformComponent->getPosition().y + other.m_size.y;

            float bx4 = other.m_transformComponent->getPosition().x;
            float by4 = other.m_transformComponent->getPosition().y + other.m_size.y;

            if (isPointInRect(sf::Vector2f(ax1, ay1), sf::Vector2f(ax2, ay2), sf::Vector2f(bx1, by1)) ||
                    isPointInRect(sf::Vector2f(ax1, ay1), sf::Vector2f(ax2, ay2), sf::Vector2f(bx2, by2)) ||
                    isPointInRect(sf::Vector2f(ax1, ay1), sf::Vector2f(ax2, ay2), sf::Vector2f(bx3, by3)) ||
                    isPointInRect(sf::Vector2f(ax1, ay1), sf::Vector2f(ax2, ay2), sf::Vector2f(bx4, by4)) ) {
                return true;
            }
            return false;
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
