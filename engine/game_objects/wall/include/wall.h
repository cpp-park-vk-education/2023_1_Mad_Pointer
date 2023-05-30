#pragma ocne
#include "game_object.h"
#include "event_listener.h"
#include "shape_component.h"
#include <SFML/Graphics.hpp>


class Wall : public GameObject<Wall> {
public:

    Wall(ecs::Engine *engine, ecs::ComponentManager* instance, sf::Vector2f pos) : m_engine(engine), m_startPos(pos),  GameObject(engine, instance, pos) {}

    ~Wall() override {}
    void onEnable() override{

    }

    virtual void OnDisable() {}

private:
    sf::Vector2f m_startPos;
    ecs::Engine* m_engine;
    TransformComponent*	m_transformComponent;
    ShapeComponent*	m_shapeComponent;
};
