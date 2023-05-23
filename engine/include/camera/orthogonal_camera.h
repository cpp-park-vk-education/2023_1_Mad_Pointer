#pragma once
#include "camera.h"
class OrthogonalCamera : public Camera {
private:

    float m_Zoom;

public:

    OrthogonalCamera(const glm::vec3& position, const float zoom = 1.0f);
    virtual ~OrthogonalCamera();

    virtual Transform GetViewTransform() const override;
    virtual Transform GetProjectionTransform() const override;

    void TurnLeft(const float degrees);
    void TurnRight(const float degrees);

    inline void SetZoom(const float zoom) {}

};
