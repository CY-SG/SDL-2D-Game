#include "CameraSystem.h"
#include"FollowTargetBehavior.h"
CameraSystem::CameraSystem(Camera2D* camera)
{
	this->camera = camera;
}

void CameraSystem::SetFollowBehavior(float lerpSpeed, Entity* entity)
{
	cameraBehavior = std::make_unique<FollowTargetBehavior>(entity,lerpSpeed);
}

void CameraSystem::Update()
{
	cameraBehavior.get()->Update(camera);
}
