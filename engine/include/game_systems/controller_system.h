#pragma once

class ControllerSystem :  public ECS::Event::IEventListener {
    using RegisteredController = std::list<Controller*>;
public:

    ControllerSystem();
    virtual ~ControllerSystem();

    void update(float deltaTime);

    void RegisterController(Controller* controller);
    void UnregisterController(Controller* controller);
private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
    RegisteredController m_Controller;
};
