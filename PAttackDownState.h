#pragma once
#include"BaseState.h"
class ActionStateMachine;
class PAttackDownState :public BaseState {
public:
	PAttackDownState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	ActionStateMachine* actionStateMachine;
private:
	float time;
};