#include "Camera2D.h"

Camera2D::Camera2D(float screenSizex, float screenSizey)
{
    screenSize = Vec2(screenSizex, screenSizey);
    pos = Vec2(-500.0f, -200.0f);
}

void Camera2D::SetPos(float x, float y)
{
    pos = Vec2(x, y);
}

Vec2 Camera2D::WorldToScreen(const Vec2& worldPos)
{
    return worldPos - pos;
}

Vec2 Camera2D::ScreenToWorld(const Vec2& screenPos)
{
    return screenPos + pos;
}

Vec2 Camera2D::GetPos()
{
    return pos;
}

Vec2 Camera2D::GetScreenSize()
{
    return screenSize;
}
