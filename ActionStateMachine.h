#pragma once
#include"StateMachine.h"
class PlayerControllerComponent;
class ActionStateMachine :public StateMachine {
public:
	void Update()override;
	StateMachine* Clone(ControllerComponent* controllerComponent)override;
	ActionStateMachine(ControllerComponent* controllerComponent);
	PlayerControllerComponent* playerControllerComponent;
private:
};