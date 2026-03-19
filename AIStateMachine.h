#pragma once
#include"StateMachine.h"
class AIControllerComponent;
class AIStateMachine :public StateMachine {
public:
	void Update()override;
	AIStateMachine(ControllerComponent* controllerComponent);
	StateMachine* Clone(ControllerComponent* controllerComponent)override;
	AIControllerComponent* aiControllerComponent;
private:
};