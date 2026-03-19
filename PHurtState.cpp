#include "PHurtState.h"
#include"ActionStateMachine.h"
#include"PlayerControllerComponent.h"
#include"EngineTime.h"
PHurtState::PHurtState(StateMachine* _stateMachine) :BaseState(_stateMachine)
{
    actionStateMachine = dynamic_cast<ActionStateMachine*>(stateMachine);
}

void PHurtState::OnEnter()
{
    time = 0.0f;
    actionStateMachine->playerControllerComponent->HandleHurtStart();
}

void PHurtState::OnUpdate()
{
    time += EngineTime::deltaTime();
    if (time >= 0.85f)actionStateMachine->ChangeToState("P_None");
}

void PHurtState::OnExit()
{
    actionStateMachine->playerControllerComponent->HandleHurtEnd();
}

BaseState* PHurtState::Clone(StateMachine* _stateMachine)
{
    PHurtState* _clone = new PHurtState(_stateMachine);
    return _clone;
}
