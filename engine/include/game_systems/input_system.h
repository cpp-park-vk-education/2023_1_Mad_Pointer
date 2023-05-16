#ifndef MY_PROJECT_INPUT_SYSTEM_H
#define MY_PROJECT_INPUT_SYSTEM_H
class InputSystem {
private:

    int				m_NumKeys;
    unsigned char*	m_OldKeyStates;

public:

    InputSystem();
    ~InputSystem();

    void PreUpdate(float deltaTime) ;

};
#endif //MY_PROJECT_INPUT_SYSTEM_H
