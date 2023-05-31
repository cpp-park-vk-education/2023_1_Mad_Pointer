#pragma once
#include "event.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

struct KeyPressedEvent : public ecs::event::Event<KeyPressedEvent> {
    int keyCode;
    KeyPressedEvent(int code) : keyCode(code) {}
};

struct KeyReleasedEvent : public ecs::event::Event<KeyReleasedEvent> {
    int keyCode;
    KeyReleasedEvent(int code) : keyCode(code) {}
};

struct LeftMouseButtonPressed : public ecs::event::Event<LeftMouseButtonPressed> {
    int xpos;
    int ypos;
    LeftMouseButtonPressed(int x, int y) : xpos(x), ypos(y) {}
};

struct LeftMouseButtonPressedWithPos : public ecs::event::Event<LeftMouseButtonPressedWithPos> {
    int xpos;
    int ypos;
    sf::Vector2f ownerPos;
    float angle;
    LeftMouseButtonPressedWithPos(int x, int y, sf::Vector2f pos, float ang) : xpos(x), ypos(y), ownerPos(std::move(pos)), angle(ang) {}
};

struct GameOverEvent : public ecs::event::Event<GameOverEvent>{};

struct GameQuitEvent : public ecs::event::Event<GameQuitEvent>{};

struct LeftButtonDownEvent : public ecs::event::Event<LeftButtonDownEvent>{
    int x;
    int y;

    LeftButtonDownEvent(int x, int y) : x(x), y(y) {}
};

struct LeftButtonUpEvent : public ecs::event::Event<LeftButtonUpEvent> {
    int x;
    int y;
    LeftButtonUpEvent(int x, int y) : x(x), y(y) {}
};

struct LeftButtonPressedEvent : public ecs::event::Event<LeftButtonPressedEvent> {
    int x;
    int y;

    LeftButtonPressedEvent(int x, int y) : x(x), y(y) {}
};

struct GameObjectCreated : public ecs::event::Event<GameObjectCreated> {
    ecs::EntityId m_EntityID;

    GameObjectCreated(ecs::EntityId id) : m_EntityID(id) {}
};

struct WallCreated : public ecs::event::Event<WallCreated> {
    ecs::EntityId m_EntityID;

    WallCreated(ecs::EntityId id) : m_EntityID(id) {}
};

struct WallDestroyed : public ecs::event::Event<WallDestroyed> {
    ecs::EntityId m_EntityID;

    WallDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct GameObjectDestroyed : public ecs::event::Event<GameObjectDestroyed> {
    ecs::EntityId m_EntityID;
    GameObjectDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct CollisionEvent : public ecs::event::Event<CollisionEvent> {
    ecs::EntityId objectA;
    ecs::EntityId objectB;

    CollisionEvent(ecs::EntityId a, ecs::EntityId b) : objectA(a), objectB(b) {}
};