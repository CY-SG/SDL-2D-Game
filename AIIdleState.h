#pragma once
#include"BaseState.h"
class AIStateMachine;
class AIIdleState :public BaseState {
public:
	AIIdleState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIStateMachine* aiStateMachine;
private:
};