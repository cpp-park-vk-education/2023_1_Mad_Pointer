#pragma once
#include "component.h"
#include <memory>
#include <SFML/Graphics.hpp>

enum CollisionType {
    EnemyCollisionType,
    PlayerCollisionType,
    ProjectileCollisionType,
    CarCollisionType,
    BoxCollisionType,
    WallCollisionType
};

class CollisionComponent : public ecs::Component<CollisionComponent> {
public:
    CollisionComponent(const ecs::EntityId id, CollisionType collisionType) : m_collisionType(collisionType) {}
    ~CollisionComponent() override = default;

    CollisionType getCollisionType() const {
        return m_collisionType;
    }

private:
    CollisionType m_collisionType;
};
