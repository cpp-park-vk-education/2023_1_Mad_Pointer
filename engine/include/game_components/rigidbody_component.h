#pragma once
class RigidbodyComponent : public ecs::Component<RigidbodyComponent> {
public:
    BodyType m_Box2DBodyType;

    float m_LinearDamping;
    float m_AngularDamping;
    float m_Friction;
    float m_Restitution;
    float m_Density;

    Body* m_Box2DBody;

    RigidbodyComponent();
    RigidbodyComponent(float friction, float restitution, float linearDamping, float angularDamping, float density);
    virtual ~RigidbodyComponent();

    void SetTransform(const Transform& transform);
    void SetScale(const vec2& scale);
};
