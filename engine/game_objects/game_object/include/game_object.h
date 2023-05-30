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
    GameObject(ecs::Engine* engine, ecs::ComponentManager* instance) : m_engine(engine), ecs::Entity<T>(instance) {}

    void onEnable() override {}

    virtual ~GameObject() {}

private:
    ecs::Engine* m_engine;
};
