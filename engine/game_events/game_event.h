#pragma once
#include "event.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

struct KeyPressedEvent : public ecs::event::Event<KeyPressedEvent> {
    int keyCode;
    explicit KeyPressedEvent(int code) : keyCode(code) {}
};

struct KeyReleasedEvent : public ecs::event::Event<KeyReleasedEvent> {
    int keyCode;
    explicit KeyReleasedEvent(int code) : keyCode(code) {}
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
    LeftMouseButtonPressedWithPos(int x, int y, sf::Vector2f pos, float ang) : xpos(x), ypos(y), ownerPos(pos), angle(ang) {}
};

struct GameOverEvent : public ecs::event::Event<GameOverEvent>{};

struct GameQuitEvent : public ecs::event::Event<GameQuitEvent>{};

struct GameObjectCreated : public ecs::event::Event<GameObjectCreated> {
    ecs::EntityId m_EntityID;
    float m_offset;

    explicit GameObjectCreated(ecs::EntityId id, float offset) : m_EntityID(id), m_offset(offset) {}
};

struct WallCreated : public ecs::event::Event<WallCreated> {
    ecs::EntityId m_EntityID;
    sf::Vector2f m_minBounds;
    sf::Vector2f m_maxBounds;

    WallCreated(ecs::EntityId id, sf::Vector2f minBounds, sf::Vector2f maxBounds) : m_EntityID(id),
                                                                                    m_minBounds(minBounds),
                                                                                    m_maxBounds(maxBounds) {}
};

struct WallDestroyed : public ecs::event::Event<WallDestroyed> {
    ecs::EntityId m_EntityID;

    explicit WallDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct GameObjectDestroyed : public ecs::event::Event<GameObjectDestroyed> {
    ecs::EntityId m_EntityID;
    explicit GameObjectDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct CarCreated : public ecs::event::Event<CarCreated> {
    ecs::EntityId m_EntityID;
    explicit CarCreated(ecs::EntityId id) : m_EntityID(id) {}
};

struct CarDestroyed : public ecs::event::Event<CarDestroyed> {
    ecs::EntityId m_EntityID;
    explicit CarDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct BoxCreated : public ecs::event::Event<BoxCreated> {
    ecs::EntityId m_EntityID;
    explicit BoxCreated(ecs::EntityId id) : m_EntityID(id) {}
};

struct BoxDestroyed : public ecs::event::Event<BoxDestroyed> {
    ecs::EntityId m_EntityID;
    explicit BoxDestroyed(ecs::EntityId id) : m_EntityID(id) {}
};

struct CollisionEvent : public ecs::event::Event<CollisionEvent> {
    ecs::EntityId objectA;
    ecs::EntityId objectB;
    CollisionEvent(ecs::EntityId a, ecs::EntityId b) : objectA(a), objectB(b) {}
};
