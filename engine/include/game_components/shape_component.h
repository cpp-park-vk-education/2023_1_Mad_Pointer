#ifndef MY_PROJECT_SHAPE_COMPONENT_H
#define MY_PROJECT_SHAPE_COMPONENT_H

class ShapeComponent : public Shape, public ShapeBufferIndex, public ecs::Component<ShapeComponent> {
    friend class RenderSystem;
    void SetShapeBufferIndex(const ShapeBufferIndex& shapeBufferIndex);
public:
    ShapeComponent(const Shape& shape);
    virtual ~ShapeComponent();
};
#endif //MY_PROJECT_SHAPE_COMPONENT_H
