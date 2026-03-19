#include "PAttackUpState.h"
#include"ActionStateMachine.h"
#include"PlayerControllerComponent.h"
#include"EngineTime.h"
PAttackUpState::PAttackUpState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    actionStateMachine = dynamic_cast<ActionStateMachine*>(stateMachine);
}

void PAttackUpState::OnEnter()
{
	actionStateMachine->playerControllerComponent->HandleAttackUp();
    time = 0;
}

void PAttackUpState::OnUpdate()
{
	time += EngineTime::deltaTime();
	if (actionStateMachine->playerControllerComponent->IsHurt)actionStateMachine->ChangeToState("P_Hurt");
	else if (time >= 0.7f)actionStateMachine->ChangeToState("P_None");
}

void PAttackUpState::OnExit()
{
}

BaseState* PAttackUpState::Clone(StateMachine* _stateMachine)
{
	PAttackUpState* _clone = new PAttackUpState(_stateMachine);
	_clone->time = 0;
	return _clone;
}
