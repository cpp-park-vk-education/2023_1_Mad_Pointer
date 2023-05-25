#pragma once
#include "event.h"
#include "entity.h"

struct KeyPressedEvent : public ecs::event::Event<KeyPressedEvent> {
    int keyCode;
    KeyPressedEvent(int code) : keyCode(code) {}
};

struct KeyReleasedEvent : public ecs::event::Event<KeyReleasedEvent> {
    int keyCode;
    KeyPressedEvent(int code) : keyCode(code) {}
};

struct LeftMouseButtonPressed : public ecs::event::Event<MouseButtonPressed> {
    int xpos;
    int ypos;
    KeyPressedEvent(int x, int y) : xpos(x), ypos(y) {}
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
    ecs::EntityTypeId m_EntityTypeID;

    GameObjectCreated(ecs::EntityId id, ecs::EntityTypeId typeId) :
            m_EntityID(id),
            m_EntityTypeID(typeId) {}
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