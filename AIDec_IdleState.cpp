#include "AIDec_IdleState.h"
#include"StateMachine.h"
#include"AIDecisionMachine.h"
#include"AIControllerComponent.h"
#include"AIInput.h"
#include"InputComponent.h"
#include<random>
#include"EngineTime.h"
#include<iostream>

AIDec_IdleState::AIDec_IdleState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiDecisionMachine = dynamic_cast<AIDecisionMachine*>(_stateMachine);
    _color = color::Green;
}

void AIDec_IdleState::OnEnter()
{

    std::cout << "决策:进入Idle状态" << std::endl;
    idleTimer = RandomFloat(1.0f, 2.0f);
}

void AIDec_IdleState::OnUpdate()
{
    auto controller = aiDecisionMachine->aiControllerComponent;
    auto& bb = controller->blackBoard;

    // 看到玩家
    if (bb.playerVisible)
    {
        aiDecisionMachine->ChangeToState("ChaseState");
        return;
    }

    idleTimer -= EngineTime::deltaTime();

    if (idleTimer <= 0)
    {
        aiDecisionMachine->ChangeToState("PatrolState");
    }
}

void AIDec_IdleState::OnExit()
{
}

BaseState* AIDec_IdleState::Clone(StateMachine* _stateMachine)
{
    return new AIDec_IdleState(_stateMachine);
}
