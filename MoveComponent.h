#pragma once
#include"Component.h"
class MoveComponent :public Component {
public:
	MoveComponent(Entity* entity, float speed);
	MoveComponent(Entity* entity);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	float Xspeed;
};