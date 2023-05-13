#include "controller_base.h"
#include "../include/event/event_listener.h"

template<class T>
class AIController : public ControllerBase, public ecs::event::EventListenerBase {
protected:
    T*	m_controlled;

public:

    AIController(const GameObjectId gameObjectId = INVALID_GAMEOBJECT_ID) : m_Pawn(nullptr) { }

    virtual ~AIController() {}

    virtual bool Possess(const GameObjectId gameObjectId) override {}

    virtual void Unpossess() override {}


    virtual GameObjectId GetPossessed() const override {}

    virtual void Update(float dt) = 0;

}; // class AIController