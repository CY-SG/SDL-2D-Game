#include "PSlideState.h"
#include"StateMachine.h"
#include"MoveStateMachine.h"
#include"PlayerControllerComponent.h"
#include"RigidBody2DComponent.h"
#include"InputComponent.h"
#include"Input.h"
#include<iostream>
PSlideState::PSlideState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
	moveStateMachine = dynamic_cast<MoveStateMachine*>(stateMachine);
}

void PSlideState::OnEnter()
{
	moveStateMachine->playerControllerComponent->HandleSlideStart();
}

void PSlideState::OnUpdate()
{
	InputComponent* inputComponent = stateMachine->controllerComponent->inputComponent;
	if (!moveStateMachine->playerControllerComponent->IsSlide)moveStateMachine->ChangeToState("P_Normal");
	if (inputComponent->input->JumpStart) {
		moveStateMachine->playerControllerComponent->HandleSlideJump();
		moveStateMachine->ChangeToState("P_Normal");
	}
}

void PSlideState::OnExit()
{
	moveStateMachine->playerControllerComponent->HandleSlideEnd();
}

BaseState* PSlideState::Clone(StateMachine* _stateMachine)
{
	return new PSlideState(_stateMachine);
}
