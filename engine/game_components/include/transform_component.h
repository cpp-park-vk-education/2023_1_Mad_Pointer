#pragma once
#include "component.h"
#include "SFML/Graphics.hpp"

class TransformComponent : public ecs::Component<TransformComponent> {
public:
    TransformComponent() {}
    TransformComponent(sf::Vector2f pos) : m_position(pos) { }

    sf::Vector2f getPosition() const {
        return m_position;
    }
    virtual ~TransformComponent();
private:
    sf::Vector2f m_position;

};
