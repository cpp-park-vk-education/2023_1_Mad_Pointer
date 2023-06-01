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

        m_texture = std::make_unique<sf::Texture>();
        m_texture->loadFromFile("image/player_sphere.jpg");
        m_texture->setSmooth(true);
        shape->setTexture(m_texture.get());

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Green);
        m_transformComponent = addComponent<TransformComponent>(m_startPos, 0.0, 0.0);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::PlayerCollisionType);
        m_radiusComponent = addComponent<RadiusComponent>(m_radius);
        m_controller.setTransform(m_transformComponent);

        m_engine->sendEvent<GameObjectCreated>(m_entityId, m_radius * 2);
        //m_engine->sendEvent<GameQuitEvent>();

    }

    virtual void OnDisable() {
        m_engine->sendEvent<GameObjectDestroyed>(m_entityId);
        m_engine->sendEvent<GameQuitEvent>();
    }
private:
    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    float m_radius = 20.0;
    std::unique_ptr<sf::Texture> m_texture;
    CollisionComponent* m_collisionComponent;
    RadiusComponent* m_radiusComponent;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;
    Controller m_controller;
};
