#include "PAttackForwardState.h"
#include"ActionStateMachine.h"
#include"PlayerControllerComponent.h"
#include"EngineTime.h"
#include<iostream>
PAttackForwardState::PAttackForwardState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
	actionStateMachine = dynamic_cast<ActionStateMachine*>(stateMachine);
}

void PAttackForwardState::OnEnter()
{
	actionStateMachine->playerControllerComponent->HandleAttackForward();
	time = 0;
}

void PAttackForwardState::OnUpdate()
{
	time += EngineTime::deltaTime();
	if (actionStateMachine->playerControllerComponent->IsHurt)actionStateMachine->ChangeToState("P_Hurt");
	else if (time >= 0.7f)actionStateMachine->ChangeToState("P_None");
}

void PAttackForwardState::OnExit()
{

}

BaseState* PAttackForwardState::Clone(StateMachine* _stateMachine)
{
	PAttackForwardState* _clone = new PAttackForwardState(_stateMachine);
	_clone->time = 0;
	return _clone;
}
