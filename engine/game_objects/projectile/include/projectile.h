#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include "collision_component.h"
#include "radius_component.h"
#include <SFML/Graphics.hpp>


class Projectile : public ecs::Entity<Projectile> {
public:

    Projectile(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos, float speed, float angle) : m_startPos(pos), m_engine(engine), ecs::Entity<Projectile>(instance), m_speed(speed), m_angle(angle) {}

    ~Projectile() override {}
    void onEnable() override {
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(m_radius, sf::Color::Yellow);

        m_collisionComponent = addComponent<CollisionComponent>(CollisionType::ProjectileCollisionType);
        m_radiusComponent = addComponent<RadiusComponent>(m_radius);
        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Yellow);
        m_transformComponent = addComponent<TransformComponent>(m_startPos, m_speed, m_angle);

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
    float m_radius = 5;
    float m_speed;
    float m_angle;
    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    CollisionComponent* m_collisionComponent;
    RadiusComponent* m_radiusComponent;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;

};