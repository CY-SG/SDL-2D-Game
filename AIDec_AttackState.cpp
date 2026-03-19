#include "AIDec_AttackState.h"
#include"StateMachine.h"
#include"AIDecisionMachine.h"
#include"AIControllerComponent.h"
#include"InputComponent.h"
#include"Input.h"
#include"EngineTime.h"
#include<iostream>
AIDec_AttackState::AIDec_AttackState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiDecisionMachine = dynamic_cast<AIDecisionMachine*>(_stateMachine);
    _color = color::Red;
}

void AIDec_AttackState::OnEnter()
{
    attackCooldown = 0.0f;
    aiDecisionMachine->aiControllerComponent->inputComponent->input->Attack = true;
    std::cout << "决策:进入攻击状态" << std::endl;
}

void AIDec_AttackState::OnUpdate()
{
    auto controller = aiDecisionMachine->aiControllerComponent;
    auto& bb = controller->blackBoard;

    attackCooldown += EngineTime::deltaTime();

    if (attackCooldown >= aiDecisionMachine->aiControllerComponent->attackCooldown)
    {
        if (bb.playerVisible)
            aiDecisionMachine->ChangeToState("ChaseState");
        else
            aiDecisionMachine->ChangeToState("IdleState");
    }
}

void AIDec_AttackState::OnExit()
{
}

BaseState* AIDec_AttackState::Clone(StateMachine* _stateMachine)
{
    return new AIDec_AttackState(_stateMachine);
}
