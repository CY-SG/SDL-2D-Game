#include "AIIdleState.h"
#include"AIControllerComponent.h"
#include"AIStateMachine.h"
#include"InputComponent.h"
#include"Input.h"
#include"CoroutineManager.h"
#include<iostream>
AIIdleState::AIIdleState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiStateMachine = dynamic_cast<AIStateMachine*>(_stateMachine);
}

void AIIdleState::OnEnter()
{
    CoroutineManager::Instance()->CancelCoroutineByEntity(aiStateMachine->aiControllerComponent->GetOwner());
    aiStateMachine->aiControllerComponent->HandleIdle(aiStateMachine->aiControllerComponent->GetOwner(), aiStateMachine->aiControllerComponent->faceleft);
    std::cout << "Action£º½øÈëIdle×´Ì¬" << std::endl;
}

void AIIdleState::OnUpdate()
{
    InputComponent* inputComponent = aiStateMachine->aiControllerComponent->inputComponent;
    if (aiStateMachine->aiControllerComponent->IsHurt) {
        aiStateMachine->ChangeToState("HurtState");
        return;
    }
    if (aiStateMachine->aiControllerComponent->CanAttack()) {
        if (inputComponent->input->Attack) {
            aiStateMachine->ChangeToState("AttackState");
            return;
        }
    }
    if (aiStateMachine->aiControllerComponent->CanJump()) {
        if (inputComponent->input->JumpStart) {
            aiStateMachine->ChangeToState("JumpState");
            return;
        }
    }
    if (aiStateMachine->aiControllerComponent->CanMove()) {
        if (inputComponent->input->MoveLeft||inputComponent->input->MoveRight) {
            aiStateMachine->ChangeToState("RunState");
            return;
        }
    }
}

void AIIdleState::OnExit()
{
}

BaseState* AIIdleState::Clone(StateMachine* _stateMachine)
{
    return new AIIdleState(_stateMachine);
}
