#pragma once
class TransformComponent : public ECS::Component<TransformComponent> {
private:
    Transform	m_Transform;
public:
    TransformComponent();
    TransformComponent(const mat3& transform);
    TransformComponent(const Transform& transform);
    virtual ~TransformComponent();
    inline void SetTransform(const glm::mat4& transform) {this->m_Transform = transform;}
    inline Transform* AsTransform() { return &(this->m_Transform); }
    inline const float*		AsFloat() const { return this->m_Transform; }
    inline const mat3& AsMat3() const { return this->m_Transform; }
};
