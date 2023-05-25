#pragma once

#include "system.h"
#include "event.h"

#include <SFML/Graphics.hpp>

class InputSystem : ecs::System<InputSystem> {
public:
    InputSystem();
    ~InputSystem();

    void preUpdate(float deltaTime) override;

private:
    sf::RenderWindow window;
};

void InputSystem::preUpdate(float deltaTime) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                // window.close();
                break;
            case sf::Event::KeyPressed:
                // pressed
                break;
            case sf::Event::KeyReleased:
                // released
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // mouse left
                    // event.mouseButton.x
                    // event.mouseButton.y
                }
                break;
            default:
                break;
        }
    }
}
