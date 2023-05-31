#pragma once
#include <SFML/Graphics.hpp>
#include "event_listener.h"
#include "engine.h"
#include "logger.h"
class GameLoop : protected ecs::event::EventListenerBase {
public:
    explicit GameLoop(const std::string& name = "Game Name") : m_gameName(name), ecs::event::EventListenerBase(nullptr) {}

    void initializeECS();
    void initializeSFML();

    void run();

    ~GameLoop() override = default;

private:
    std::string m_gameName;
     sf::RenderWindow m_window;
    ecs::Engine m_engine;
};
