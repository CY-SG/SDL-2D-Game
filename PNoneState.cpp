#include "PNoneState.h"
#include"ActionStateMachine.h"
#include"PlayerControllerComponent.h"
#include"AnimationComponent.h"
#include"InputComponent.h"
#include"Input.h"
#include<iostream>
PNoneState::PNoneState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
	actionStateMachine = dynamic_cast<ActionStateMachine*>(stateMachine);
}

void PNoneState::OnEnter()
{
	actionStateMachine->playerControllerComponent->SetAnimationActive(false, 1);
}

void PNoneState::OnUpdate()
{
	InputComponent* inputComponent = actionStateMachine->playerControllerComponent->inputComponent;
	if (actionStateMachine->playerControllerComponent->IsHurt)actionStateMachine->ChangeToState("P_Hurt");
	else if (inputComponent->input->Attack) {
		if (inputComponent->input->Down)actionStateMachine->ChangeToState("P_AttackDown");
		else if (inputComponent->input->Up)actionStateMachine->ChangeToState("P_AttackUp");
		else actionStateMachine->ChangeToState("P_AttackForward");
	}
}

void PNoneState::OnExit()
{
	actionStateMachine->playerControllerComponent->SetAnimationActive(true, 1);
}

BaseState* PNoneState::Clone(StateMachine* _stateMachine)
{
	PNoneState* _clone = new PNoneState(_stateMachine);
	return _clone;
}
