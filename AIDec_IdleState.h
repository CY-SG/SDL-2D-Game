#pragma once
#include"BaseState.h"
class AIDecisionMachine;
class AIDec_IdleState :public BaseState {
public:
	AIDec_IdleState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIDecisionMachine* aiDecisionMachine;
	float idleTimer;
};