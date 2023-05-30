#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include <SFML/Graphics.hpp>


class Enemy : public GameObject<Enemy> {
public:

    Enemy(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_startPos(pos), m_engine(engine), GameObject(engine, instance) {

    }

    ~Enemy() override {}
    void onEnable() override {
        std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(20, sf::Color::Red);

        m_shapeComponent = addComponent<ShapeComponent>(std::move(shape), sf::Color::Red);
        m_transformComponent = addComponent<TransformComponent>(m_startPos, 0.0, 0.0);
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