#pragma once
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include "radius_component.h"
#include <SFML/Graphics.hpp>

class Enemy : public GameObject<Enemy> {
public:
    Enemy(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_startPos(pos), m_engine(engine), GameObject(engine, instance) {}

    ~Enemy() override {
        OnDisable();
    }
    void onEnable() override {
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(m_radius, sf::Color::Red);

        m_texture = std::make_unique<sf::Texture>();
        m_texture->loadFromFile("image/enemy_sphere.jpg");
        m_texture->setSmooth(true);
        shape->setTexture(m_texture.get());

        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::EnemyCollisionType);
        m_radiusComponent = addComponent<RadiusComponent>(m_radius);
        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Red);
        m_transformComponent = addComponent<TransformComponent>(m_startPos, 0.0, 0.0);

        m_engine->sendEvent<GameObjectCreated>(m_entityId, m_radius * 2);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<GameObjectDestroyed>(m_entityId);
        m_engine->sendEvent<EnemyDestroyed>();
    }
private:
    float m_radius = 20.0;
    std::unique_ptr<sf::Texture> m_texture;

    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    CollisionComponent* m_collisionComponent;
    RadiusComponent* m_radiusComponent;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;

};
