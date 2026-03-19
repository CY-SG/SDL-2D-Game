#pragma once
#include"Component.h"
#include<unordered_set>
class DamageComponent :public Component {
public:
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	DamageComponent(Entity* entity, int damage, float duration);
	int damage;
	std::unordered_set<Entity*>attackTarget;
	float currTime;
	float duration;
private:
};