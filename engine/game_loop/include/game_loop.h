#pragma once
#include <SFML/Graphics.hpp>
#include "event_listener.h"
#include "engine.h"
#include "logger.h"
class GameLoop : protected ecs::event::EventListenerBase {
public:
    GameLoop(const std::string& name = "Game Name") : m_gameName(name), ecs::event::EventListenerBase(nullptr) {}

    void initializeECS();
    void initializeSFML();

    void processWindowEvent();
    //void Initialize(int width, int height) {}
    void run();

    ~GameLoop() {}

private:
    std::string m_gameName;

    bool m_isRunning = false;
     sf::RenderWindow m_window;

    ecs::Engine m_engine;
};
