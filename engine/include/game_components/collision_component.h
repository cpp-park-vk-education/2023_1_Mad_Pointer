#pragma once
class CollisionComponent2D : public Component<CollisionComponent2D> {
private:
    ShapeID	shapeID;
public:
    Shape::Type shapeType;
    CircleShape asCircleShape;
    PolygonShape asPolygonShape;
    uint16 collisionCategory;
    uint16 collisionMask;
    bool isSensor;

    CollisionComponent2D(const Shape& shape, const glm::vec2& scale = glm::vec2(1.0f), uint16 category = 0x0001, uint16 mask = 0xffff);
    virtual ~CollisionComponent2D();
    void Rescale(const vec2& scale);
};
