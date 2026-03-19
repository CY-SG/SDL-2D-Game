#pragma once
#include"ControllerComponent.h"
#include<string>
#include<memory>
class AISensorController :public ControllerComponent {
public:
	AISensorController(Entity* entity);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
private:
};