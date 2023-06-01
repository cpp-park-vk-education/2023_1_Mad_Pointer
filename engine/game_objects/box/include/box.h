#pragma once
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include "car_controller.h"

#include <SFML/Graphics.hpp>

constexpr float BOX_SPEED = 5.0;
constexpr float BOX_ANGLE = 90;

class Box : public GameObject<Box> {
public:
    Box(ecs::Engine *engine, ecs::ComponentManager* instance, const sf::Vector2f& pos, const sf::Vector2f& size) : m_engine(engine), GameObject(engine, instance),
                                                                                                                    m_pos(pos), m_size(size) {}

    ~Box() override {
        onDisable();
    }
    void onEnable() override {
        std::unique_ptr<RectangleShapeFill> shape = std::make_unique<RectangleShapeFill>(m_pos, m_size, sf::Color::Black);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Blue);
        m_transformComponent = addComponent<TransformComponent>(m_pos, BOX_SPEED, BOX_ANGLE);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::BoxCollisionType);

        m_engine->sendEvent<BoxCreated>(m_entityId);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<BoxDestroyed>(m_entityId);
    }
private:
    sf::Vector2f m_size;
    sf::Vector2f m_pos;

    ecs::Engine* m_engine;
    ShapeComponent*	m_shapeComponent;
    TransformComponent* m_transformComponent;
    CollisionComponent* m_collisionComponent;
};