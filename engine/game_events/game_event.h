#include "event.h"
#include "entity.h"
#include <SDL2/SDL_keycode.h>

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


struct KeyDownEvent : public ecs::event::Event<KeyDownEvent> {
    SDL_Keycode keyCode;
    KeyDownEvent(SDL_Keycode key) : keyCode(key) {}
};

struct KeyUpEvent : public ecs::event::Event<KeyUpEvent> {
    SDL_Keycode keyCode;
    KeyUpEvent(SDL_Keycode code) : keyCode(code) {}
};

struct KeyPressedEvent : public ecs::event::Event<KeyPressedEvent> {
    SDL_Keycode keyCode;
    KeyPressedEvent(SDL_Keycode code) : keyCode(code) {}
};

struct GameObjectCreated : public ecs::event::Event<GameObjectCreated> {
    ecs::EntityId m_EntityID;
    ecs::EntityTypeId m_EntityTypeID;

    GameObjectCreated(EntityId id, EntityTypeId typeId) :
            m_EntityID(id),
            m_EntityTypeID(typeId) {}
};

struct CollisionEvent : public ecs::event::Event<CollisionEvent> {
    GameObjectId objectA;
    GameObjectId objectB;

    CollisionBeginEvent(GameObjectId a, GameObjectId b) : objectA(a), objectB(b) {}
};
