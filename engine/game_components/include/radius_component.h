#pragma once
#include "component.h"
#include "SFML/Graphics.hpp"

class RadiusComponent : public ecs::Component<RadiusComponent> {
public:

    RadiusComponent(const ecs::EntityId id, float radius) : m_radius(radius) { }

    float getRadius() const {
        return m_radius;
    }
    ~RadiusComponent() override {}
private:
    float m_radius;
};
