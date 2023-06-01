#pragma once

#include "system.h"
#include "engine.h"
#include "game_event.h"

#include <SFML/Graphics.hpp>

class InputSystem : public ecs::System<InputSystem> {
public:
    InputSystem(sf::RenderWindow& window, ecs::Engine* engine) : m_engine(engine), m_window(window) {}
    ~InputSystem() override = default;

    void preUpdate(float deltaTime) override;

private:
    sf::RenderWindow& m_window;
    ecs::Engine* m_engine;
};

void InputSystem::preUpdate(float deltaTime) {
    sf::Event event{};
    if (!m_window.isOpen()) return;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                m_engine->sendEvent<KeyPressedEvent>(event.key.code);
                break;
            case sf::Event::KeyReleased:
                m_engine->sendEvent<KeyReleasedEvent>(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    m_engine->sendEvent<LeftMouseButtonPressed>(event.mouseButton.x, event.mouseButton.y);
                }
                break;
            case sf::Event::Closed:
                    m_window.close();
                break;
            default:
                break;
        }
    }
}
