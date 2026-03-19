#include "AIRunState.h"
#include"AIControllerComponent.h"
#include"AIStateMachine.h"
#include"InputComponent.h"
#include"Input.h"
#include<iostream>
AIRunState::AIRunState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiStateMachine = dynamic_cast<AIStateMachine*>(_stateMachine);
}

void AIRunState::OnEnter()
{
    std::cout << "Action£º½øÈëRun×´Ì¬" << std::endl;
}

void AIRunState::OnUpdate()
{
    aiStateMachine->aiControllerComponent->HandleRun(aiStateMachine->aiControllerComponent->GetOwner(), aiStateMachine->aiControllerComponent->faceleft);
    if (aiStateMachine->aiControllerComponent->IsHurt) {
        aiStateMachine->ChangeToState("HurtState");
        return;
    }
    if (aiStateMachine->aiControllerComponent->inputComponent->input->Attack ) {
        aiStateMachine->ChangeToState("AttackState");
    }
    else if (!aiStateMachine->aiControllerComponent->inputComponent->input->MoveLeft && !aiStateMachine->aiControllerComponent->inputComponent->input->MoveRight) {
        aiStateMachine->ChangeToState("IdleState");
    }
}

void AIRunState::OnExit()
{
}

BaseState* AIRunState::Clone(StateMachine* _stateMachine)
{
    return new AIRunState(_stateMachine);
}
