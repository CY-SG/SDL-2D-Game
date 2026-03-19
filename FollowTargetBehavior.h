#pragma once
#include"CameraBehavior.h"
class Entity;
class FollowTargetBehavior:public CameraBehavior {
public:
	FollowTargetBehavior(Entity*entity,float t);
	void SetEntity(Entity* entity);
	void SetLerpSpeed(float t);
	void Update(Camera2D* camera) override;
private:
	Vec2 Lerp(const Vec2& from, const Vec2& to, float t);
	Entity* entity;
	float lerpSpeed;
};