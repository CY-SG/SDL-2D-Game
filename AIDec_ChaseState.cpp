#include "AIDec_ChaseState.h"
#include"StateMachine.h"
#include"AIDecisionMachine.h"
#include"AIControllerComponent.h"
#include"AIInput.h"
#include"InputComponent.h"
#include<iostream>
#include"EngineTime.h"
#include"Entity.h"
#include"TransformComponent.h"
AIDec_ChaseState::AIDec_ChaseState(StateMachine* _stateMachine):BaseState(_stateMachine)
{
    aiDecisionMachine = dynamic_cast<AIDecisionMachine*>(_stateMachine);
    _color = color::Yellow;
}

void AIDec_ChaseState::OnEnter()
{
    JumpCooldown = 0.0f;
    aiDecisionMachine->aiControllerComponent->aiMoveMode = AIMoveMode::AIMoveChase;
    std::cout << "决策:进入追击状态" << std::endl;
}

void AIDec_ChaseState::OnUpdate()
{
    auto controller = aiDecisionMachine->aiControllerComponent;
    auto& bb = controller->blackBoard;
    auto input = controller->inputComponent->input;
    JumpCooldown += EngineTime::deltaTime();

    // 如果有目标 → 朝玩家方向移动
    if (bb.target)
    {
        Vec2 playerPos =
            bb.target->GetComponent<TransformComponent>()->worldpos;

        Vec2 myPos =
            controller->GetOwner()
            ->GetComponent<TransformComponent>()
            ->worldpos;

        if (playerPos.x < myPos.x)
        {
            controller->faceleft = true;
            input->MoveLeft = true;
        }
        else
        {
            controller->faceleft = false;
            input->MoveRight = true;
        }
    }
    else
    {
        // 没有目标继续沿当前方向追
        if (controller->faceleft)
            input->MoveLeft = true;
        else
            input->MoveRight = true;
    }

    //进入攻击范围
    if (bb.playerInAttackRange)
    {
        aiDecisionMachine->ChangeToState("AttackState");
        return;
    }

    // 碰到墙 / 悬崖 → 转向
    if (bb.wallAhead || !bb.groundAhead)
    {
        controller->FlipDir();
        return;
    }

    if (!bb.upperWall && bb.lowerWall && controller->IsGround&&JumpCooldown>=controller->jumpCooldown) {
        float temp = RandomFloat(0, 1.0f);
        if (temp <= 0.3f) {
            input->JumpStart = true;
            JumpCooldown = 0.0f;
        }
    }

    // 超过记忆时间 → 停止追逐
    if (bb.loseSightTimer >= controller->visibleMemoryTime)
    {
        aiDecisionMachine->ChangeToState("IdleState");
        return;
    }
}

void AIDec_ChaseState::OnExit()
{
}

BaseState* AIDec_ChaseState::Clone(StateMachine* _stateMachine)
{
    return new AIDec_ChaseState(_stateMachine);
}
