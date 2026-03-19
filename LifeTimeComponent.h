#pragma once
#include"Component.h"
class LifeTimeComponent :public Component {
public:
	LifeTimeComponent(Entity* entity, float _Lifetime);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	float Lifetime = 0;
	float curLifeTime = 0;
private:
};