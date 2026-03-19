#pragma once
#include"BaseState.h"
class AIStateMachine;
class AIHurtState :public BaseState {
public:
	AIHurtState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIStateMachine* aiStateMachine;
private:
	float time;
	float HurtTime;
};