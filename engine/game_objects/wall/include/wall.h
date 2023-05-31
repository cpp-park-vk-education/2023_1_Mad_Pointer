#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"

#include <SFML/Graphics.hpp>

class Wall : public GameObject<Wall> {
public:
    Wall(ecs::Engine *engine, ecs::ComponentManager* instance, const std::vector<sf::Vector2f>& vertices) : m_engine(engine), GameObject(engine, instance) {
        for (const auto& v : vertices) {
            m_verticesForBounds.emplace_back(v);
        }
    }

    ~Wall() override = default;
    void onEnable() override {
        std::unique_ptr<RectangleShape> shape = std::make_unique<RectangleShape>(m_verticesForBounds);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::White);
        m_transformComponent = addComponent<TransformComponent>(sf::Vector2f(), 0.0, 0.0);
        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::WallCollisionType);

        sf::Vector2f minBounds = m_verticesForBounds[0].position;
        sf::Vector2f maxBounds = m_verticesForBounds[2].position;
        m_engine->sendEvent<WallCreated>(m_entityId, minBounds, maxBounds);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<WallDestroyed>(m_entityId);
    }
private:
    std::vector<sf::Vertex> m_verticesForBounds;
    ecs::Engine* m_engine;
    ShapeComponent*	m_shapeComponent;
    TransformComponent* m_transformComponent;
    CollisionComponent* m_collisionComponent;
};
