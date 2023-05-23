#pragma once
#include "event_listener.h"
#include "engine.h"

class GameLoop : protected ecs::event::EventListenerBase {
public:
    void InitializeECS() {}
    void InitializeSDL() {}
    void ProcessWindowEvent() {}
    void Terminate() {}

public:
    GameLoop(const std::string& name = "Game Name") {}
    ~GameLoop() {}
    void Initialize(int width, int height) {}
    void Run() {}
};
