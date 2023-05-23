#pragma once
class TabletopCamera : public GameCamera<OrthoCamera> {
public:
    TabletopCamera(const vec2& position, const float zOffset, const float zoom = 1.0f);
    virtual ~TabletopCamera();
};
