#pragma once
#include "component.h"
#include "SFML/Graphics.hpp"

class TransformComponent : public ecs::Component<TransformComponent> {
public:
    TransformComponent() {}

    TransformComponent(const ecs::EntityId id, sf::Vector2f pos, float speed, float angle) : m_position(pos),
                                                                                             m_speed(speed),
                                                                                             m_angle(angle) {}

    sf::Vector2f getPosition() const {
        return m_position;
    }

    float getAngle() const {
        return m_angle;
    }

    float getSpeed() {
        return m_speed;
    }

    void setAngle(float angle) {
        m_angle = angle;
    }

    void setSpeed(float speed) {
        m_speed = speed;
    }

    void changePosition(sf::Vector2f dpos) {
        m_position += dpos;
    }

    ~TransformComponent() override {}

private:
    sf::Vector2f m_position;
    float m_speed;
    float m_angle;
};
