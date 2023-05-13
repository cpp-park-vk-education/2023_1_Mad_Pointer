#ifndef MY_PROJECT_CONTROLLER_SYSTEM_H
#define MY_PROJECT_CONTROLLER_SYSTEM_H

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


#endif //MY_PROJECT_CONTROLLER_SYSTEM_H
