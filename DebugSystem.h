#pragma once
#include"System.h"
class Render;
class Camera2D;
class DebugSystem:public System {
public:
	DebugSystem(Render* render, Camera2D* camera);
	void Update()override;
private:
	void RenderPhysics();
	void RenderAIState();
	int frameCount = 0;
	float currTime = 0;
	Render* render;
	Camera2D* camera;
};