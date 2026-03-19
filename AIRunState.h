#pragma once
#include"BaseState.h"
class AIStateMachine;
class AIRunState :public BaseState {
public:
	AIRunState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIStateMachine* aiStateMachine;
private:
};