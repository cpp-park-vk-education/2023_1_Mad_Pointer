#pragma once
#include <SFML/Graphics.hpp>
#include "event_listener.h"
#include "engine.h"
#include "logger.h"


class GameLoop : protected ecs::event::EventListenerBase {
public:
    explicit GameLoop(const std::string& name, const std::string& path) : m_gameName(name), m_pathToBackground(path), ecs::event::EventListenerBase(nullptr) {}

    virtual void initializeECS() = 0;
    void initializeSFML();

    void run();

    ~GameLoop() override = default;

private:
    std::string m_pathToBackground;
    std::string m_gameName;
protected:
    ecs::Engine m_engine;
    sf::RenderWindow m_window;
};
