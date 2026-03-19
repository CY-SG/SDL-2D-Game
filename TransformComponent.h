#pragma once
#include"Component.h"
#include"Math.h"
#include<vector>
class TransformComponent :public Component {
public:
	std::unique_ptr<Component>Clone(Entity* entity)override;
	TransformComponent(Entity* entity,Entity*parent=nullptr);
	Vec2 pos;
	Vec2 worldpos;
	void Update() override;
	TransformComponent* parent;
	std::vector<TransformComponent*>child;
private:
	void UpdateTransform();
};