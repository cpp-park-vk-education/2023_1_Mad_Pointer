#pragma once

#include "system.h"
#include "engine.h"
#include "game_events.h"

#include <SFML/Graphics.hpp>

class InputSystem : ecs::System<InputSystem> {
public:
    InputSystem();
    ~InputSystem();

    void preUpdate(float deltaTime) override;

private:
    sf::RenderWindow window;
    ecs::Engine* engine;
};

void InputSystem::preUpdate(float deltaTime) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                KeyPressedEvent ev(event.key.code);
                engine->sendEvent(ev);
                break;
            case sf::Event::KeyReleased:
                KeyReleasedEvent ev(event.key.code);
                engine->sendEvent(ev);
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    LeftMouseButtonPressed ev(event.mouseButton.x, event.mouseButton.y);
                    engine->sendEvent(ev);
                }
                break;
            default:
                break;
        }
    }
}
