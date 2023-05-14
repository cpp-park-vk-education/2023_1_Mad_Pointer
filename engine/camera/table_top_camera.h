#ifndef MY_PROJECT_TABLE_TOP_CAMERA_H
#define MY_PROJECT_TABLE_TOP_CAMERA_H
class TabletopCamera : public GameCamera<OrthoCamera> {
public:
    TabletopCamera(const glm::vec2& position, const float zOffset, const float zoom = 1.0f);
    virtual ~TabletopCamera();
};
#endif //MY_PROJECT_TABLE_TOP_CAMERA_H
