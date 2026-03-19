#include "AIHurtState.h"
#include"StateMachine.h"
#include"AIStateMachine.h"
#include"PlayerControllerComponent.h"
#include"AIControllerComponent.h"
#include"CoroutineManager.h"
#include"EngineTime.h"
#include"AnimationComponent.h"
#include<iostream>
AIHurtState::AIHurtState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    time = 0;
    aiStateMachine = dynamic_cast<AIStateMachine*>(_stateMachine);
    HurtTime = aiStateMachine->aiControllerComponent->hurtCoolddown;
}

void AIHurtState::OnEnter()
{
    time = 0;
    std::cout << "½øÈëHurt×´Ì¬" << std::endl;
    aiStateMachine->aiControllerComponent->HandleHurtStart();
    CoroutineManager::Instance()->CancelCoroutineByEntity(aiStateMachine->aiControllerComponent->GetOwner());
    if (aiStateMachine->aiControllerComponent->HandleHurt)
        aiStateMachine->aiControllerComponent->HandleHurt(aiStateMachine->aiControllerComponent->GetOwner(), aiStateMachine->aiControllerComponent->faceleft);
}

void AIHurtState::OnUpdate()
{
    time += EngineTime::deltaTime();
    if (time >= HurtTime) {
        aiStateMachine->ChangeToState("IdleState");
        return;
    }
}

void AIHurtState::OnExit()
{
    aiStateMachine->aiControllerComponent->IsHurt = false;
}

BaseState* AIHurtState::Clone(StateMachine* _stateMachine)
{
    return new AIHurtState(_stateMachine);
}
