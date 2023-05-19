#pragma once
#include "../event/event_listener.h"
#include "../engine/engine.h"

class GameLoop : protected ecs::event::EventListenerBase {
public:
    void InitializeECS() {}
    void InitializeSDL() {}
    void ProcessWindowEvent() {}
    void Terminate() {}

public:
    GameLoop(const char* name = "Game Name") {}
    ~GameLoop() {}
    void Initialize(int width, int height) {}
    void Run() {}
};
