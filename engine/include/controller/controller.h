#pragma once
#include "player_controller.h"

class Controller {
private:
    ControllerBase* m_ControllerImpl;
public:

    Controller(IController* controllerImpl);

    ~Controller();

    void Release();

    void SetController(IController* controllerImpl);

    bool SwapController(IController* controllerImpl);

    bool Possess(const GameObjectId gameObjectId);

    void Unpossess();

    GameObjectId GetPossessed();

    void Update(float deltaTime);

};