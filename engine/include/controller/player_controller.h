#pragma once
#include "controller_base.h"
#include "../event/event_listener.h"
template<class T>
class PlayerController : ControllerBase, ecs::event::EventListenerBase {
protected:
    T* m_controlled;
private:
    void OnKeyDownInternal(const KeyDownEvent* event) {

    }

    void OnKeyUpInternal(const KeyUpEvent* event) {

    }

    void OnKeyPressedInternal(const KeyPressedEvent* event) {
    }

    void OnGamePaused(const GamePausedEvent* event) {
    }

    void OnGameResumed(const GameResumedEvent* event) { }

public:

    PlayerController(const GameObjectId gameObjectId = INVALID_GAMEOBJECT_ID) : m_Pawn(nullptr) {}

    virtual ~PlayerController() {}

    virtual bool Possess(const GameObjectId gameObjectId) override {}

    virtual void Unpossess() override {}

    virtual GameObjectId GetPossessed() const override {}

    virtual void Update(float deltaTime) = 0;

    virtual void OnKeyDown(const KeyDownEvent* event) = 0;
    virtual void OnKeyUp(const KeyUpEvent* event) = 0;
    virtual void OnKeyPressed(const KeyPressedEvent* event) = 0;

};
