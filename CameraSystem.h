#pragma once
#include<memory>
#include"CameraBehavior.h"
class Camera2D;
class Entity;
class CameraSystem {
public:
	CameraSystem(Camera2D* camera);
	void SetFollowBehavior(float lerpSpeed,Entity*entity);
	void Update();
	Camera2D* camera;
private:
	std::unique_ptr<CameraBehavior>cameraBehavior;
};