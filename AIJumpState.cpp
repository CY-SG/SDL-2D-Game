#include "AIJumpState.h"
#include"AIControllerComponent.h"
#include"AIStateMachine.h"
#include"InputComponent.h"
#include"Input.h"
AIJumpState::AIJumpState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    aiStateMachine = dynamic_cast<AIStateMachine*>(_stateMachine);
}

void AIJumpState::OnEnter()
{
    aiStateMachine->aiControllerComponent->HandleJump(aiStateMachine->aiControllerComponent->GetOwner(), aiStateMachine->aiControllerComponent->faceleft);
}

void AIJumpState::OnUpdate()
{
    if (aiStateMachine->aiControllerComponent->IsGround) {
        aiStateMachine->ChangeToState("IdleState");
        return;
    }
}

void AIJumpState::OnExit()
{
}

BaseState* AIJumpState::Clone(StateMachine* _stateMachine)
{
    return new AIJumpState(_stateMachine);
}
