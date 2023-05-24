#pragma once

#include "system.h"
#include "event.h"

class InputSystem : ecs::System<InputSystem> {
public:
    InputSystem();
    ~InputSystem();

    void preUpdate(float deltaTime) override;

private:
    int	m_NumKeys;
    unsigned char* m_OldKeyStates;
};
