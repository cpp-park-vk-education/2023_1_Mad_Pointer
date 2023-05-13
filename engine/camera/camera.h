#ifndef MY_PROJECT_CAMERA_H
#define MY_PROJECT_CAMERA_H

class Camera {
protected:
    float m_Near;
    float m_Far;
    vec2 m_Position;
    vec2 m_Left;
    vec2 m_Up;
    vec2 m_Forward;
    vec2 m_Viewport;
public:
    Camera();
    virtual ~Camera();

    virtual Transform GetViewTransform() const = 0;
    virtual Transform GetProjectionTransform() const = 0;

    inline void SetPosition(const vec2& position) { this->m_Position = position; }
    inline void SetViewport(const vec2& viewport) { this->m_Viewport = viewport; }

};
#endif //MY_PROJECT_CAMERA_H
