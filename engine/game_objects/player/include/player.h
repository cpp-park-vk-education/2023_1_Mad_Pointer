#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include <SFML/Graphics.hpp>


class Player : public GameObject<Player> {
public:

    Player(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_engine(engine), m_startPos(pos),  GameObject(engine, instance) {}

    ~Player() override {}
    void onEnable() override{
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(20, sf::Color::Green);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Green);
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
    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;
};
