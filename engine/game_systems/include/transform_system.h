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

                sf::Vector2f dpos(dx, dy);
                movable.getTransform()->changePosition(dpos);
            }
        }
    }

    struct Movable {
    public:
        Movable(ecs::EntityBase* entity, TransformComponent* transform) : m_entity(entity),
                                                                          m_entityId(entity->getEntityId()),
                                                                          m_transformComponent(transform) {}

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

    private:
        ecs::EntityId m_entityId;
        bool m_isActive = true;
        ecs::EntityBase* m_entity;
        TransformComponent* m_transformComponent;
    };

private:
    void registerEventCallbacks() {
        registerEventCallback(&TransformSystem::onGameObjectCreated);
        registerEventCallback(&TransformSystem::onGameObjectDestroyed);
    }

    void onGameObjectDestroyed(const GameObjectDestroyed* event) {
        m_killedObjs.insert(event->m_EntityID);
    }

    void onGameObjectCreated(const GameObjectCreated* event) {
        auto entity = getEngine()->getEntityManager()->getEntity(event->m_EntityID);
        if (!entity) return;
        auto transform = entity->getComponent<TransformComponent>();

        registerMovable(entity, transform);
    }

    void registerMovable(ecs::EntityBase* entity, TransformComponent* transform) {
        m_movable.emplace_back(entity, transform);
    }

    void unregisterEventCallbacks() {
        unregisterEventCallback(&TransformSystem::onGameObjectCreated);
        registerEventCallback(&TransformSystem::onGameObjectDestroyed);
    }
private:
    std::set<ecs::EntityId> m_killedObjs;
    std::vector<Movable> m_movable;
};

/*
    vel.x = sin((PI/180)*angle) * speed * time;
    vel.y = cos((PI/180)*angle)* speed * time;

    pos = pos + vel;
*/