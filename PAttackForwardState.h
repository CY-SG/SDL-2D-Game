#pragma once
#include"BaseState.h"
class ActionStateMachine;
class PAttackForwardState :public BaseState {
public:
	PAttackForwardState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	ActionStateMachine* actionStateMachine;
private:
	float time;
};