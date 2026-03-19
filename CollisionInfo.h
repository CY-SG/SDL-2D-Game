#pragma once
#include"Math.h"
class Entity;
struct CollisionInfo {
	Entity* a;
	Entity* b;
	Vec2 normal;
	float penetration;
	bool IsTrigger;
};