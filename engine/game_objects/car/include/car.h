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
        onDisable();
    }
    void onEnable() override {
        std::unique_ptr<RectangleShapeFill> shape = std::make_unique<RectangleShapeFill>(m_pos, m_size, sf::Color::Blue);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Blue);
        m_transformComponent = addComponent<TransformComponent>(m_pos, 0.0, 0.0);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::CarCollisionType);

        m_carController.setTransform(m_transformComponent);
        m_engine->sendEvent<CarCreated>(m_entityId);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<CarDestroyed>(m_entityId);
    }
private:
    sf::Vector2f m_size;
    sf::Vector2f m_pos;

    CarController m_carController;
    ecs::Engine* m_engine;
    ShapeComponent*	m_shapeComponent;
    TransformComponent* m_transformComponent;
    CollisionComponent* m_collisionComponent;
};