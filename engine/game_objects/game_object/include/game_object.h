#pragma once
#include "entity.h"
#include "engine.h"
#include "component_manager.h"
#include "transform_component.h"
#include "game_event.h"
#include <SFML/Graphics.hpp>

template<class T>
class GameObject : public ecs::Entity<T> {
public:
    GameObject(ecs::Engine* engine, ecs::ComponentManager* instance) : m_engine(engine), ecs::Entity<T>(instance) {
        this->template addComponent<TransformComponent>(sf::Vector2<float>(5, 5));
        m_engine->sendEvent<GameObjectCreated>(this->getEntityId());
    }

    virtual ~GameObject() {
        m_engine->sendEvent<GameObjectDestroyed>(this->getEntityId());
    }

private:
    ecs::Engine* m_engine;
};
