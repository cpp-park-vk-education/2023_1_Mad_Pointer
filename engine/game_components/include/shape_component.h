#pragma once
#include "component.h"
#include <memory>
#include <SFML/Graphics.hpp>

class ShapeBase {
public:
    virtual ~ShapeBase() = default;
    virtual void renderShape(sf::RenderWindow& window) const = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
};

class CircleShape : public ShapeBase {
public:
    CircleShape(float radius, sf::Color color) : m_circle(radius) {
        setColor(color);
    }

    void setPosition(const sf::Vector2f& position) override {
        m_circle.setPosition(position);
    }

    void renderShape(sf::RenderWindow& window) const override {
        window.draw(m_circle);
    }

    CircleShape& setColor(sf::Color color) {
        m_circle.setFillColor(color);
        return *this;
    }
private:
    sf::CircleShape m_circle;
};

class ShapeComponent : public ecs::Component<ShapeComponent> {
public:
    ShapeComponent(const ecs::EntityId id, std::unique_ptr<ShapeBase> shape, sf::Color color) : m_shape(std::move(shape)), m_color(color) {}
    ~ShapeComponent() override {}

    sf::Color getColor() const { return  m_color; }

    void render(sf::RenderWindow& window, sf::Vector2f pos) const {
        if (m_shape) {
            m_shape->setPosition(pos);
            m_shape->renderShape(window);
        }
    }
private:
    std::unique_ptr<ShapeBase> m_shape;
    sf::Color m_color = sf::Color::Black;
};
