#pragma once
#include"BaseState.h"
class ActionStateMachine;
class PNoneState :public BaseState {
public:
	PNoneState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	ActionStateMachine* actionStateMachine;
private:
};