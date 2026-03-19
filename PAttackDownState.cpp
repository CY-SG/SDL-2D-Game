#include "PAttackDownState.h"
#include"ActionStateMachine.h"
#include"PlayerControllerComponent.h"
#include"EngineTime.h"
PAttackDownState::PAttackDownState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    actionStateMachine = dynamic_cast<ActionStateMachine*>(stateMachine);
}

void PAttackDownState::OnEnter()
{
	actionStateMachine->playerControllerComponent->HandleAttackDown();
    time = 0;
}

void PAttackDownState::OnUpdate()
{
	time += EngineTime::deltaTime();
	if (actionStateMachine->playerControllerComponent->IsHurt)actionStateMachine->ChangeToState("P_Hurt");
	else if (time >= 0.7f)actionStateMachine->ChangeToState("P_None");
}

void PAttackDownState::OnExit()
{
}

BaseState* PAttackDownState::Clone(StateMachine* _stateMachine)
{
	PAttackDownState* _clone = new PAttackDownState(_stateMachine);
	_clone->time = 0;
	return _clone;
}
