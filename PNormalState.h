#pragma once
#include"BaseState.h"
class MoveStateMachine;
class PNormalState :public BaseState {
public:
	PNormalState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	MoveStateMachine* moveStateMachine;
private:
};