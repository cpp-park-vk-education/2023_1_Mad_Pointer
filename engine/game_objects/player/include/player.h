#pragma once
#include "controller.h"
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "radius_component.h"
#include "collision_component.h"
#include <SFML/Graphics.hpp>

class Player : public GameObject<Player> {
public:

    Player(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_engine(engine), m_startPos(pos), m_controller(engine), GameObject(engine, instance) {}

    ~Player() override  {
        OnDisable();
    }
    void onEnable() override{
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(m_radius, sf::Color::Green);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Green);
        m_transformComponent = addComponent<TransformComponent>(m_startPos, 0.0, 0.0);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::PlayerCollisionType);
        m_radiusComponent = addComponent<RadiusComponent>(m_radius);
        m_controller.setTransform(m_transformComponent);

        m_engine->sendEvent<GameObjectCreated>(m_entityId);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<GameObjectDestroyed>(m_entityId);
    }
private:
    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    float m_radius = 20.0;
    CollisionComponent* m_collisionComponent;
    RadiusComponent* m_radiusComponent;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;
    Controller m_controller;
};
