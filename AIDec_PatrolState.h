#pragma once
#include"BaseState.h"
class AIDecisionMachine;
class AIDec_PatrolState :public BaseState {
public:
	AIDec_PatrolState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIDecisionMachine* aiDecisionMachine;

	float patrolTime = 0.0f;
	float JumpCooldown = 0.0f;
};