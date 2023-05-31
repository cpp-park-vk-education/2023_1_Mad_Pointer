#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include <cmath>

#define PI 3.14159265

class TransformSystem : public ecs::System<TransformSystem>, public ecs::event::EventListenerBase {
public:
    explicit TransformSystem(ecs::Engine* engine) : ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~TransformSystem() override { unregisterEventCallbacks(); }

    void update(float dt) override {
        for (auto& movable : m_movable) {
            float dx = std::cos((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();
            float dy = std::sin((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();

            if (movable.getTransform()->getPosition().x + dx < m_bounds[0].position.x ||
                movable.getTransform()->getPosition().x + dx > m_bounds[2].position.x - movable.getOffset()) {
                  dx = 0;
            }
            if (movable.getTransform()->getPosition().y + dy < m_bounds[0].position.y ||
                movable.getTransform()->getPosition().y + dy > m_bounds[2].position.y - movable.getOffset()) {
                  dy = 0;
            }

            sf::Vector2f dpos(dx, dy);
            movable.getTransform()->changePosition(dpos);
        }
    }

    struct Movable {
    public:
        Movable(ecs::EntityBase* entity, TransformComponent* transform, float offset) : m_entity(entity),
                                                                                        m_transformComponent(transform),
                                                                                        m_offset(offset) {}

        ~Movable() = default;

        TransformComponent* getTransform() {
            return m_transformComponent;
        }

        float getOffset() {
            return m_offset;
        }

    private:
        ecs::EntityBase* m_entity;
        TransformComponent* m_transformComponent;
        float m_offset;
    };

private:
    void registerEventCallbacks() {
        registerEventCallback(&TransformSystem::onGameObjectCreated);
        registerEventCallback(&TransformSystem::onWallCreated);
        registerEventCallback(&TransformSystem::onWallDestroyed);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform, event->m_offset);
    }

    void registerMovable(ecs::EntityBase* entity, TransformComponent* transform, float offset) {
        m_movable.emplace_back(entity, transform, offset);
    }

    void onWallCreated(const WallCreated* event) {
        m_bounds = event->m_verticesForBounds;
    }

    void onWallDestroyed(const WallDestroyed* event) {}

    void unregisterEventCallbacks() {
        unregisterEventCallback(&TransformSystem::onGameObjectCreated);
    }
private:
    std::vector<Movable> m_movable;
    std::vector<sf::Vertex> m_bounds;
};
