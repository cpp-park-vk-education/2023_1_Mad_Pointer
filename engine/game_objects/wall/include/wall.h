#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include <SFML/Graphics.hpp>

class Wall : public GameObject<Wall> {
public:
    Wall(ecs::Engine *engine, ecs::ComponentManager* instance, std::vector<sf::Vector2f> vertices) : m_engine(engine), GameObject(engine, instance) {
        for (const auto& v : vertices) {
            m_verticesForBounds.emplace_back(v);
        }
    }

    ~Wall() override = default;
    void onEnable() override {
        std::unique_ptr<RectangleShape> shape = std::make_unique<RectangleShape>(m_verticesForBounds);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::White);
        m_transformComponent = addComponent<TransformComponent>(sf::Vector2f());
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::WallCollisionType);
        m_engine->sendEvent<WallCreated>(m_entityId);
    }

    virtual void OnDisable() {}
private:
    std::vector<sf::Vertex> m_verticesForBounds;
    ecs::Engine* m_engine;
    ShapeComponent*	m_shapeComponent;
    TransformComponent* m_transformComponent;
    CollisionComponent* m_collisionComponent;
};
