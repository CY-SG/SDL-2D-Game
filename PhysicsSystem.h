#pragma once
#include"System.h"
#include"CollisionInfo.h"
#include"Math.h"
#include<vector>
class Entity;
class Collider2DComponent;
class PhysicsSystem :public System {
public:
	void Update()override;
private:
	void ApplyGravity();
	void ApplyTransform();
	void CheckCollider();
	bool ColliderAABB(const Vec2& apos, const Vec2& asize, const Vec2& bpos, const Vec2& bsize);
	bool CheckLayer(Collider2DComponent* colliderA, Collider2DComponent* colliderB);
	void ResolveCollision(Entity* entityA, Entity* entityB);
	void UpdateTransform();
	void HandleInfo();
	std::vector<CollisionInfo>collisionInfoes;
};