#pragma once
#include"BaseState.h"
class AIDecisionMachine;
class AIDec_AttackState :public BaseState {
public:
	AIDec_AttackState(StateMachine* _stateMachine);
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
	BaseState* Clone(StateMachine* _stateMachine)override;
	AIDecisionMachine* aiDecisionMachine;
	float attackCooldown;
};