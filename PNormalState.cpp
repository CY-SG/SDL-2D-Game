#include "PNormalState.h"
#include"StateMachine.h"
#include"InputComponent.h"
#include"ControllerComponent.h"
#include"MoveStateMachine.h"
#include"PlayerControllerComponent.h"
#include"Input.h"
#include<iostream>
PNormalState::PNormalState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
	moveStateMachine = dynamic_cast<MoveStateMachine*>(stateMachine);
}

void PNormalState::OnEnter()
{
}

void PNormalState::OnUpdate()
{
	InputComponent* inputComponent = stateMachine->controllerComponent->inputComponent;
	if (moveStateMachine->playerControllerComponent->CanMove()) {
		if (inputComponent->input->MoveLeft) {
			moveStateMachine->playerControllerComponent->HandleRun(true);
			moveStateMachine->playerControllerComponent->faceLeft = true;
		}
		else if (inputComponent->input->MoveRight) {
			moveStateMachine->playerControllerComponent->HandleRun(false);
			moveStateMachine->playerControllerComponent->faceLeft = false;
		}
	}
	if (!inputComponent->input->MoveLeft && !inputComponent->input->MoveRight)moveStateMachine->playerControllerComponent->SetXSpeed(0.0f);

	if (inputComponent->input->JumpStart) {
		std::cout << "°´ÏÂÌøÔ¾¼ü" << std::endl;
		moveStateMachine->playerControllerComponent->HandleJumpStart();
	}
	if (inputComponent->input->JumpIng) {
		moveStateMachine->playerControllerComponent->HandleJumpIng();
	}
	if (inputComponent->input->JumpEnd) {
		moveStateMachine->playerControllerComponent->HandleJumpEnd();
	}
	if (moveStateMachine->playerControllerComponent->IsSlide)moveStateMachine->ChangeToState("P_Slide");
}

void PNormalState::OnExit()
{
}

BaseState* PNormalState::Clone(StateMachine* _stateMachine)
{
	return new PNormalState(_stateMachine);
}
