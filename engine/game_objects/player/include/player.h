#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include <SFML/Graphics.hpp>


class Player : public GameObject<Player> {
public:

    Player(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : GameObject(engine, instance) {
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(1, sf::Color::Green);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Green);
        m_transformComponent = getComponent<TransformComponent>();
    }

    ~Player() override {}
    virtual void OnEnable() {}

    virtual void OnDisable() {}

    void MoveForward(float speed);
    void TurnLeft(float degrees);
    void TurnRight(float degrees);
    void Stop();

    void StopTurning();
    void StopMoving();


private:
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;

}; // class Collector
