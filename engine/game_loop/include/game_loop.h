#pragma once
#include <SDL2/SDL.h>
#include "event_listener.h"
#include "engine.h"
#include "logger.h"
class GameLoop : protected ecs::event::EventListenerBase {
public:
    GameLoop(const std::string& name = "Game Name") : m_gameName(name) {}

    void InitializeECS();
    void InitializeSDL(int width, int height);

    void ProcessWindowEvent() {}
    //void Initialize(int width, int height) {}
    void Run();

    ~GameLoop() {}

private:
    std::string m_gameName;

    bool m_isRunning = false;
    SDL_Window* m_window = nullptr;

    ecs::Engine m_engine;
};
