#pragma once
#include"Input.h"
#include<memory>
class AIDecisionMachine;
class AIInput :public Input {
public:
	AIInput();
	void Update()override;
	Input* Clone()override;
private:
};