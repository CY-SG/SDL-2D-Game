#pragma once
#include"BaseState.h"
class AIStateMachine;
class AIJumpState :public BaseState {
public:
	AIJumpState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIStateMachine* aiStateMachine;
private:
};