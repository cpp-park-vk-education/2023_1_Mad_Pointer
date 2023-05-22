#pragma once
#include "component.h"
#include "vector2.h"

class CollisionComponent2D : public ecs::Component<CollisionComponent2D> {
private:
    ShapeID	shapeID;

public:
    Shape::Type shapeType;
    CircleShape asCircleShape;
    PolygonShape asPolygonShape;
    uint16 collisionCategory;
    uint16 collisionMask;
    bool isSensor;

    CollisionComponent2D(const Shape& shape, const Vec2& scale = Vec2(1.0f, 1.0f), uint16 category = 0x0001, uint16 mask = 0xffff);
    virtual ~CollisionComponent2D();
    void Rescale(const Vec2& scale);
};
