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

class CollisionSystem : public ecs::System<CollisionSystem>, public ecs::event::EventListenerBase {
public:
    explicit CollisionSystem(ecs::Engine* engine) : m_engine(engine), ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }
    ~CollisionSystem() override { unregisterEventCallbacks(); }

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
                    //m_engine->sendEvent<CollisionEvent>(m_rigidBodies[i].getEntityId(), m_rigidBodies[j].getEntityId());
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
        RigidBody(ecs::EntityBase* entity, TransformComponent* transform, CollisionComponent* collisionComponent, float radius) :
                m_entity(entity),
                m_entityId(entity->getEntityId()),
                m_transformComponent(transform),
                m_collisionComponent(collisionComponent),
                m_radius(radius) {}

        ~RigidBody() = default;

        bool checkCollision(const RigidBody& other) const {
            auto x = m_transformComponent->getPosition().x - other.m_transformComponent->getPosition().x;
            auto y = m_transformComponent->getPosition().y - other.m_transformComponent->getPosition().y;
            auto distantion = sqrt(x * x + y * y);
            if (distantion <= m_radius + other.m_radius) {
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
        float m_radius;
        ecs::EntityBase* m_entity;
        CollisionComponent*	m_collisionComponent;
        TransformComponent* m_transformComponent;
    };

    using RigidBodyVector = std::vector<RigidBody>;
private:
    void handleCollision(const RigidBody& objectA, const RigidBody& objectB) {
        if (objectA.getCollisionType() == CollisionType::PlayerCollisionType && objectB.getCollisionType() == CollisionType::EnemyCollisionType) {
            m_pendingToDestroy.push_back(objectA.getEntityId());
        } else if (objectA.getCollisionType() == CollisionType::EnemyCollisionType && objectB.getCollisionType() == CollisionType::PlayerCollisionType) {
            m_pendingToDestroy.push_back(objectB.getEntityId());
        } else if (objectA.getCollisionType() == CollisionType::EnemyCollisionType && objectB.getCollisionType() == CollisionType::ProjectileCollisionType) {
            m_pendingToDestroy.push_back(objectA.getEntityId());
            m_pendingToDestroy.push_back(objectB.getEntityId());
        } else if (objectA.getCollisionType() == CollisionType::ProjectileCollisionType && objectB.getCollisionType() == CollisionType::EnemyCollisionType) {
            m_pendingToDestroy.push_back(objectA.getEntityId());
            m_pendingToDestroy.push_back(objectB.getEntityId());
        } else {}
    }

    [[maybe_unused]] void registerEventCallbacks() {
        registerEventCallback(&CollisionSystem::onGameObjectCreated);
        registerEventCallback(&CollisionSystem::onGameObjectDestroyed);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();
        auto collision = entity->getComponent<CollisionComponent>();
        float radius = entity->getComponent<RadiusComponent>()->getRadius();
        registerRigidBody(entity, transform, collision, radius);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        unregisterRigidBody(event->m_EntityID);
    }

    [[maybe_unused]] void unregisterEventCallbacks() {
        unregisterEventCallback(&CollisionSystem::onGameObjectCreated);
        unregisterEventCallback(&CollisionSystem::onGameObjectDestroyed);
    }

    void registerRigidBody(ecs::EntityBase* entity, TransformComponent* transform, CollisionComponent* collisionComponent, float radius) {
        m_rigidBodies.emplace_back(entity, transform, collisionComponent, radius);
    }

    void unregisterRigidBody(ecs::EntityId gameObjectId) {
        m_killedObjects.insert(gameObjectId);
    }

    ecs::Engine* m_engine;
    RigidBodyVector m_rigidBodies;
    std::unordered_set<ecs::EntityId> m_killedObjects;
    std::vector<ecs::EntityId> m_pendingToDestroy;
};
