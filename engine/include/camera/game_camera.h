#ifndef MY_PROJECT_GAME_CAMERA_H
#define MY_PROJECT_GAME_CAMERA_H
class GameCameraBase {
public:
    virtual ~GameCameraBase() {}
    virtual EntityId GetCameraID() const = 0;
    virtual Transform GetProjectionTransform() = 0;
    virtual Transform GetViewTransform() = 0;
};

template<class Camera>
class GameCamera : public GameCameraBase, public GameObject<Camera>, public ecs::event::EventListenerBase {
private:

    Transform m_ViewTransform;
    Transform m_ProjectionTransform;

    TransformComponent* m_ThisTransformComponent;

    void OnWindowResized(const WindowResizedEvent* event) {}

protected:

    Camera*	m_Camera;
public:

    template<class... ARGS>
    GameCamera(ARGS&... args) : m_Camera(new Camera(std::forward<ARGS>(args)...)), m_ThisTransformComponent(nullptr) {}

    virtual ~GameCamera() {}

    virtual EntityId GetCameraID() const { }

    virtual Transform GetProjectionTransform() {}

    virtual Transform GetViewTransform() {}
    inline void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {}

};
#endif //MY_PROJECT_GAME_CAMERA_H
