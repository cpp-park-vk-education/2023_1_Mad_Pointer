#pragma once
class InputSystem {
private:

    int	m_NumKeys;
    unsigned char* m_OldKeyStates;

public:
    InputSystem();
    ~InputSystem();

    void PreUpdate(float deltaTime) ;

};
