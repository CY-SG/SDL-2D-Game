#pragma once
#include"Component.h"
class HpComponent :public Component {
public:
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	HpComponent(Entity* entity,int Hp);
	int maxHp;
	int currHp;
	void TakeDamage(int damage);
private:
};