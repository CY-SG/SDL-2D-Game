#pragma once
#include"StateMachine.h"
class AIControllerComponent;
class Input;
class AIDecisionMachine :public StateMachine {
public:
	void Update()override;
	AIDecisionMachine(ControllerComponent* controllerComponent);
	StateMachine* Clone(ControllerComponent* controllerComponent)override;
	AIControllerComponent* aiControllerComponent;
private:
};