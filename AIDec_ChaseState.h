#pragma once
#include"BaseState.h"
class AIDecisionMachine;
class AIDec_ChaseState :public BaseState {
public:
	AIDec_ChaseState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIDecisionMachine* aiDecisionMachine;
	float JumpCooldown = 0.0f;
};