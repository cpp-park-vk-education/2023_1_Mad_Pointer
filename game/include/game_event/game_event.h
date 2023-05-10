#include "../game_types/game_types.h"

struct GameInitializedEvent : public ecs::event::Event<GameInitializedEvent> {};

struct GameRestartedEvent : public ecs::event::Event<GameRestartedEvent>{};

struct GameStartedEvent : public ecs::event::Event<GameStartedEvent>{};

struct GamePausedEvent : public ecs::event::Event<GamePausedEvent> {};

struct GameResumedEvent : public ecs::event::Event<GameResumedEvent>{};

struct GameoverEvent : public ecs::event::Event<GameoverEvent>{};

struct GameQuitEvent : public ecs::event::Event<GameQuitEvent>{};

struct PauseGameEvent : public ecs::event::Event<PauseGameEvent>{};

struct ResumeGameEvent : public ecs::event::Event<ResumeGameEvent>{};

struct RestartGameEvent : public ecs::event::Event<RestartGameEvent>{};

struct QuitGameEvent : public ecs::event::Event<QuitGameEvent>{};

#include <SDL_keycode.h>

struct LeftButtonDownEvent : public ecs::event::Event<LeftButtonDownEvent>{
    int x;
    int y;

    LeftButtonDownEvent(int x, int y) : x(x), y(y) {}
};

struct LeftButtonUpEvent : public ecs::event::Event<LeftButtonUpEvent> {
    int x;
    int y;

    LeftButtonUpEvent(int x, int y) : x(x), y(y)
    {}
};

struct LeftButtonPressedEvent : public ecs::event::Event<LeftButtonPressedEvent> {
    int x;
    int y;

    LeftButtonPressedEvent(int x, int y) : x(x), y(y)
    {}
};

struct RightButtonDownEvent : public ecs::event::Event<RightButtonDownEvent> {
    int x;
    int y;

    RightButtonDownEvent(int x, int y) : x(x), y(y)
    {}
};

struct RightButtonUpEvent : public ecs::event::Event<RightButtonUpEvent> {
    int x;
    int y;

    RightButtonUpEvent(int x, int y) : x(x), y(y)
    {}
};

struct RightButtonPressedEvent : public ecs::event::Event<RightButtonPressedEvent>
{
    int x;
    int y;

    RightButtonPressedEvent(int x, int y) : x(x), y(y) {}
};


struct KeyDownEvent : public ecs::event::Event<KeyDownEvent> {
    SDL_Keycode keyCode;

    KeyDownEvent(SDL_Keycode key) : keyCode(key) {}
};

struct KeyUpEvent : public ecs::event::Event<KeyUpEvent> {
    SDL_Keycode keyCode;

    KeyUpEvent(SDL_Keycode code) : keyCode(code)
    {}
};

struct KeyPressedEvent : public ecs::event::Event<KeyPressedEvent> {
    SDL_Keycode keyCode;

    KeyPressedEvent(SDL_Keycode code) : keyCode(code)
    {}
};

struct GameObjectCreated : public ecs::event::Event<GameObjectCreated> {
    GameObjectId		m_EntityID;
    GameObjectTypeId	m_EntityTypeID;

    GameObjectCreated(GameObjectId id, GameObjectTypeId typeId) :
            m_EntityID(id),
            m_EntityTypeID(typeId)
    {}
};

struct GameObjectDestroyed : public ecs::event::Event<GameObjectDestroyed> {
    GameObjectId		m_EntityID;
    GameObjectTypeId	m_EntityTypeID;

    GameObjectDestroyed(GameObjectId id, GameObjectTypeId typeId) :
            m_EntityID(id),
            m_EntityTypeID(typeId)
    {}
};

struct GameObjectSpawned : public ecs::event::Event<GameObjectSpawned> {
    GameObjectId	m_EntityID;
    Transform		m_Transform;

    GameObjectSpawned(GameObjectId id, const Transform& transform) :
            m_EntityID(id),
            m_Transform(transform)
    {}
};

struct GameObjectKilled : public ecs::event::Event<GameObjectKilled> {
    GameObjectId	m_EntityID;

    GameObjectKilled(GameObjectId id) : m_EntityID(id) {}
};

struct CameraCreated : public ecs::event::Event<CameraCreated> {
    GameObjectId cameraID;

    CameraCreated(GameObjectId id) : cameraID(id) {}
};

struct CameraDestroyed : public ecs::event::Event<CameraDestroyed> {
    GameObjectId cameraID;

    CameraDestroyed(GameObjectId id) : cameraID(id)
    {}
};


struct WindowMinimizedEvent : public ecs::event::Event<WindowMinimizedEvent> {};

struct WindowRestoredEvent : public ecs::event::Event<WindowRestoredEvent> {};

struct WindowResizedEvent : public ecs::event::Event<WindowResizedEvent> {
    int width;
    int height;

    WindowResizedEvent(int w, int h) : width(w), height(h) {}
};


//Game Events
struct PlayerJoined : public ecs::event::Event<PlayerJoined> {
    PlayerId playerID;

    PlayerJoined(PlayerId id) : playerID(id)
    {}
};

struct PlayerLeft : public ecs::event::Event<PlayerLeft> {
    PlayerId playerID;

    PlayerLeft(PlayerId id) : playerID(id)
    {}
};

struct PlayerDied : public ecs::event::Event<PlayerDied> {
    PlayerId playerID;

    PlayerDied(PlayerId id) : playerID(id)
    {}
};

struct PlayerSpawned : public ecs::event::Event<PlayerSpawned> {
    PlayerId playerID;

    PlayerSpawned(PlayerId id) : playerID(id)
    {}
};

struct StashFull : public ecs::event::Event<StashFull> {
    GameObjectId stashId;

    StashFull(GameObjectId id) : stashId(id)
    {}
};

struct PlayerPocketFillStateChange : public ecs::event::Event<PlayerPocketFillStateChange> {
    PlayerId playerID;
    float fillState;

    PlayerPocketFillStateChange(PlayerId id, float fill) : playerID(id), fillState(fill)
    {}
};

struct PlayerStashFillStateChange : public ecs::event::Event<PlayerStashFillStateChange> {
    PlayerId playerID;
    float fillState;

    PlayerStashFillStateChange(PlayerId id, float fill) : playerID(id), fillState(fill) {}
};


// Collisions
struct CollisionBeginEvent : public ecs::event::Event<CollisionBeginEvent> {
    GameObjectId objectA;
    GameObjectId objectB;

    struct collisionDetails
    {
        CollisionCategory collisionCategoryA;
        CollisionCategory collisionCategoryB;

        CollisionMask collisionMaskA;
        CollisionMask collisionMaskB;
    } details;

    CollisionBeginEvent(GameObjectId a, GameObjectId b) : objectA(a), objectB(b) {}

};

struct CollisionEndEvent : public ecs::event::Event<CollisionEndEvent> {
    GameObjectId objectA;
    GameObjectId objectB;

    struct collisionDetails
    {
        CollisionCategory collisionCategoryA;
        CollisionCategory collisionCategoryB;

        CollisionMask collisionMaskA;
        CollisionMask collisionMaskB;
    } details;

    CollisionEndEvent(GameObjectId a, GameObjectId b) : objectA(a), objectB(b)
    {}

}; // struct CollisionEndEvent

