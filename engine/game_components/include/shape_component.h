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
    CircleShape(float radius, sf::Color color) : m_circle(radius, 50) {
        m_circle.setRadius(radius);
        setColor(color);
    }

    void setPosition(const sf::Vector2f& position) override {
        m_circle.setPosition(position);
    }

    void renderShape(sf::RenderWindow& window) const override {
        window.draw(m_circle, sf::RenderStates::Default);
    }

    CircleShape& setColor(sf::Color color) {
        m_circle.setFillColor(color);
        return *this;
    }

    void setTexture(sf::Texture* texture) {
        m_circle.setTexture(texture);
    }
private:
    sf::CircleShape m_circle;
};

class RectangleShape : public ShapeBase {
public:
    RectangleShape(const std::vector<sf::Vertex>& vertices): m_vertices(sf::LinesStrip, 5){
        m_vertices.clear();
        for (const auto& v : vertices) {
            m_vertices.append(v);
        }
    }

    ~RectangleShape() override {}
    RectangleShape& setColor(sf::Color color) {}

    void setPosition(const sf::Vector2f& position) override {}

    void renderShape(sf::RenderWindow& window) const override {
        window.draw(m_vertices);
    }
private:
    sf::VertexArray m_vertices;
};

class RectangleShapeFill : public ShapeBase {
public:
    RectangleShapeFill(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Color color, bool flag = false): m_rectangle(size) {
        if (!flag)
        setColor(color);
    }

    ~RectangleShapeFill() override {}

    void setPosition(const sf::Vector2f& position) override {
        m_rectangle.setPosition(position.x, position.y);
    }

    void renderShape(sf::RenderWindow& window) const override {
        window.draw(m_rectangle);
    }

    RectangleShapeFill& setColor(sf::Color color) {
        m_rectangle.setFillColor(color);
        return *this;
    }

    void setTexture(sf::Texture* texture) {
        m_rectangle.setTexture(texture);
    }
private:
    sf::RectangleShape m_rectangle;
};

class ShapeComponent : public ecs::Component<ShapeComponent> {
public:
    ShapeComponent(const ecs::EntityId id, std::unique_ptr<ShapeBase> shape, sf::Color color) : m_shape(std::move(shape)), m_color(color) {}
    ~ShapeComponent() override = default;

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
