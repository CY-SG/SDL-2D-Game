#include "AIAttackState.h"
#include"AIControllerComponent.h"
#include"AIStateMachine.h"
#include"InputComponent.h"
#include"Input.h"
#include"EngineTime.h"
#include"Entity.h"
#include"CoroutineManager.h"
#include"RigidBody2DComponent.h"
#include<iostream>
AIAttackState::AIAttackState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
    time = 0;
    aiStateMachine = dynamic_cast<AIStateMachine*>(_stateMachine);
    AttackTime = aiStateMachine->aiControllerComponent->attackCooldown;
}

void AIAttackState::OnEnter()
{
    std::cout << "Action£º½øÈëAttack×´Ì¬" << std::endl;
    aiStateMachine->aiControllerComponent->HandleAttackStart();
    CoroutineManager::Instance()->CancelCoroutineByEntity(aiStateMachine->aiControllerComponent->GetOwner());
    aiStateMachine->aiControllerComponent->GetOwner()->GetComponent<RigidBody2DComponent>()->velocity.x = 0;
    if (aiStateMachine->aiControllerComponent->HandleAttack)
    aiStateMachine->aiControllerComponent->HandleAttack(aiStateMachine->aiControllerComponent->GetOwner(),aiStateMachine->aiControllerComponent->faceleft);
    time = 0;
}

void AIAttackState::OnUpdate()
{
    time += EngineTime::deltaTime();
    if (aiStateMachine->aiControllerComponent->IsHurt) {
        aiStateMachine->ChangeToState("HurtState");
        return;
    }
    if (time >= AttackTime) {
        aiStateMachine->ChangeToState("IdleState");
        return;
    }
}

void AIAttackState::OnExit()
{
}

BaseState* AIAttackState::Clone(StateMachine* _stateMachine)
{
    return new AIAttackState(_stateMachine);
}
