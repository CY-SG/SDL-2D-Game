#pragma once
#include"Component.h"
#include<functional>
enum PhysicsLayer {
	Default = 1 << 0,
	Wall = 1 << 1,
	Player = 1 << 2,
	Enemy = 1 << 3,
	EnemyTrigger = 1 << 4
};
class Collider2DComponent :public Component {
public:
	Collider2DComponent(Entity* entity,const Vec2& _size,const Vec2& _offset,PhysicsLayer layer,uint32_t _mask);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	Vec2 size;
	bool IsTrigger;
	Vec2 offset;
	PhysicsLayer layer;
	uint32_t mask = 0xFFFFFFFF;
	void SetOnCollision(std::function<void(Entity* entityA, Entity* entityB)>onCollision_event);
	void SetOnTrigger(std::function<void(Entity* entityA, Entity* entityB)>onTrigger_event);
	std::function<void(Entity* entityA, Entity* entityB)>onCollision;
	std::function<void(Entity* entityA, Entity* entityB)>onTrigger;
private:

};