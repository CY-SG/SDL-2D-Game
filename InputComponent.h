#pragma once
#include"Component.h"
class Input;
class InputComponent :public Component {
public:
	InputComponent(Entity* entity, Input* input);
	InputComponent(Entity* entity);
	std::unique_ptr<Component>Clone(Entity* entity)override;
	void Update()override;
	Input* input;
};