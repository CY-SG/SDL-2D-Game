#include "AIDec_PatrolState.h"
#include"StateMachine.h"
#include"AIDecisionMachine.h"
#include"AIControllerComponent.h"
#include"AIInput.h"
#include"InputComponent.h"
#include"EngineTime.h"
#include<iostream>
AIDec_PatrolState::AIDec_PatrolState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiDecisionMachine = dynamic_cast<AIDecisionMachine*>(_stateMachine);
    _color = color::Blue;
}

void AIDec_PatrolState::OnEnter()
{
    aiDecisionMachine->aiControllerComponent->aiMoveMode = AIMoveMode::AIMoveNormal;
    std::cout << "决策:进入巡逻状态" << std::endl;
    patrolTime = 0.0f;
    JumpCooldown = 0.0f;
}

void AIDec_PatrolState::OnUpdate()
{
    auto controller = aiDecisionMachine->aiControllerComponent;
    auto& bb = controller->blackBoard;

    patrolTime += EngineTime::deltaTime();
    JumpCooldown += EngineTime::deltaTime();
    // 巡逻移动
    if (controller->faceleft)
        controller->inputComponent->input->MoveLeft = true;
    else
        controller->inputComponent->input->MoveRight = true;

    // 遇墙或悬崖
    if (bb.wallAhead || !bb.groundAhead)
    {
        controller->FlipDir();
    }

    if (!bb.upperWall && bb.lowerWall && controller->IsGround && JumpCooldown >= controller->jumpCooldown) {
        float temp = RandomFloat(0, 1.0f);
        if (temp <= 0.3f) {
            controller->inputComponent->input->JumpStart = true;
            JumpCooldown = 0.0f;
        }
    }

    // 看到玩家
    if (bb.playerVisible)
    {
        aiDecisionMachine->ChangeToState("ChaseState");
        return;
    }

    // 巡逻结束
    if (patrolTime >= controller->patrolTime)
    {
        aiDecisionMachine->ChangeToState("IdleState");
    }
}

void AIDec_PatrolState::OnExit()
{
}

BaseState* AIDec_PatrolState::Clone(StateMachine* _stateMachine)
{
    return new AIDec_PatrolState(_stateMachine);
}
