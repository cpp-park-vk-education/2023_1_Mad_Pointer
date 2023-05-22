#pragma once
#include "component.h"

class ShapeComponent : public Shape, public ShapeBufferIndex, public ecs::Component<ShapeComponent> {
    friend class RenderSystem;
    void SetShapeBufferIndex(const ShapeBufferIndex& shapeBufferIndex);
public:
    ShapeComponent(const Shape& shape);
    virtual ~ShapeComponent();
};
