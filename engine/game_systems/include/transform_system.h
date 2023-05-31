#pragma once
#include "system.h"
#include "event_listener.h"
#include "transform_component.h"
#include "game_event.h"
#include <cmath>

#define PI 3.14159265

class TransformSystem : public ecs::System<TransformSystem>, public ecs::event::EventListenerBase {
public:
    TransformSystem(ecs::Engine* engine) : ecs::event::EventListenerBase(engine) {
        registerEventCallbacks();
    }

    ~TransformSystem() override { unregisterEventCallbacks(); }

    void update(float dt) override {
        for (auto& movable : m_movable) {
            float dx = std::cos((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();
            float dy = std::sin((PI / 180) * movable.getTransform()->getAngle()) * movable.getTransform()->getSpeed();
            
            sf::Vector2f dpos(dx, dy);
            movable.getTransform()->changePosition(dpos);
        }
    }

    struct Movable {
    public:
        Movable(ecs::EntityBase* entity, TransformComponent* transform) : m_entity(entity),
                                                                          m_transformComponent(transform) {}

        ~Movable() = default;

        TransformComponent* getTransform() {
            return m_transformComponent;
        }

    private:
        ecs::EntityBase* m_entity;
        TransformComponent* m_transformComponent;
    };

private:
    void registerEventCallbacks() {
        registerEventCallback(&TransformSystem::onGameObjectCreated);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform);
    }

    void registerMovable(ecs::EntityBase* entity, TransformComponent* transform) {
        m_movable.emplace_back(entity, transform);
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&TransformSystem::onGameObjectCreated);
    }

private:
    std::vector<Movable> m_movable;
};

/*
    vel.x = sin((PI/180)*angle) * speed * time;
    vel.y = cos((PI/180)*angle)* speed * time;

    pos = pos + vel;
*/