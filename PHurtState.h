#pragma once
#include"BaseState.h"
class ActionStateMachine;
class PHurtState :public BaseState {
public:
	PHurtState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	ActionStateMachine* actionStateMachine;
	float time = 0;
private:
};