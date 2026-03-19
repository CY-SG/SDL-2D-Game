#pragma once
#include"StateMachine.h"
class PlayerControllerComponent;
class MoveStateMachine :public StateMachine {
public:
	void Update()override;
	StateMachine* Clone(ControllerComponent* controllerComponent)override;
	MoveStateMachine(ControllerComponent* controllerComponent);
	PlayerControllerComponent* playerControllerComponent;
private:
};