#pragma once
#include<vector>
#include"Component.h"
#include"Math.h"
struct CollideContact {
	Entity* other;
	Vec2 normal;
};
class RigidBody2DComponent :public Component {
public:
	RigidBody2DComponent(Entity* entity);
	std::unique_ptr<Component>Clone(Entity* entity)override;
	void Update()override;
	Vec2 velocity;
	bool useGravity;
	float gravityScale;
	std::vector<CollideContact>collideContact;
};