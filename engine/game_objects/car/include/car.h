#pragma once
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include "car_controller.h"

#include <SFML/Graphics.hpp>

class Car : public GameObject<Car> {
public:
    Car(ecs::Engine *engine, ecs::ComponentManager* instance, const sf::Vector2f& pos, const sf::Vector2f& size) : m_engine(engine), GameObject(engine, instance),
                                                                                                                   m_carController(engine), m_pos(pos), m_size(size) {}

    ~Car() override {
        OnDisable();
    }
    void onEnable() override {
        std::unique_ptr<RectangleShapeFill> shape = std::make_unique<RectangleShapeFill>(m_pos, m_size, sf::Color::Red, true);

        m_texture = std::make_unique<sf::Texture>();
        m_texture->loadFromFile("image/car.png");
        m_texture->setSmooth(true);
        shape->setTexture(m_texture.get());

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Blue);
        m_transformComponent = addComponent<TransformComponent>(m_pos, 0.0, 0.0);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::CarCollisionType);

        m_carController.setTransform(m_transformComponent);
        m_engine->sendEvent<CarCreated>(m_entityId, m_size);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<GameObjectDestroyed>(m_entityId);
        m_engine->sendEvent<GameQuitEvent>();
    }
private:
    sf::Vector2f m_size;
    sf::Vector2f m_pos;
    std::unique_ptr<sf::Texture> m_texture;
    CarController m_carController;
    ecs::Engine* m_engine;
    ShapeComponent*	m_shapeComponent;
    TransformComponent* m_transformComponent;
    CollisionComponent* m_collisionComponent;
};