#pragma once
#include"Math.h"
class Camera2D {
public:
	Camera2D(float screenSizex, float screenSizey);
	void SetPos(float x, float y);
	Vec2 WorldToScreen(const Vec2& worldPos);
	Vec2 ScreenToWorld(const Vec2& screenPos);
	Vec2 GetPos();
	Vec2 GetScreenSize();
private:
	Vec2 pos;
	Vec2 screenSize;
};