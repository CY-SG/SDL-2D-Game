#pragma once
#include"System.h"
class Render;
class Camera2D;
class RenderSystem :public System {
public:
	void Update()override;
	RenderSystem(Render* render,Camera2D*camera);
	bool DebugMode = true;
private:
	void RenderPhysics();
	Render* render;
	Camera2D* camera;
};