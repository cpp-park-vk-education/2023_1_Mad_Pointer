#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include "radius_component.h"
#include <SFML/Graphics.hpp>


class Enemy : public GameObject<Enemy> {
public:

    Enemy(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_startPos(pos), m_engine(engine), GameObject(engine, instance) {

    }

    ~Enemy() override {}
    void onEnable() override {
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(m_radius, sf::Color::Red);

        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::EnemyCollisionType);
        m_radiusComponent = addComponent<RadiusComponent>(m_radius);
        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Red);
        m_transformComponent = addComponent<TransformComponent>(m_startPos);

        m_engine->sendEvent<GameObjectCreated>(m_entityId);
    }

    virtual void OnDisable() {
        m_engine->sendEvent<GameObjectDestroyed>(m_entityId);
    }

    void MoveForward(float speed);
    void TurnLeft(float degrees);
    void TurnRight(float degrees);
    void Stop();

    void StopTurning();
    void StopMoving();


private:
    float m_radius = 20.0;

    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    CollisionComponent* m_collisionComponent;
    RadiusComponent* m_radiusComponent;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;

};