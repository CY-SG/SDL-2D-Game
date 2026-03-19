#pragma once
#include"ControllerStrategy.h"
#include"PlayerState.h"
class PlayerControllerStrategy :public ControllerStrategy {
public:
	PlayerControllerStrategy();
	void Update()override;
private:
	void UpdateMoveState();
	void HandleInput();
	void UpdateActionState();
	bool CanMove();
	bool CanJump();
	ActionState actionState;
	ActionState preactionState;
};