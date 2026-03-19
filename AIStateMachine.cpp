#include "AIStateMachine.h"
#include"ControllerComponent.h"
#include"AIControllerComponent.h"
#include"BaseState.h"
#include"AIAttackState.h"
#include"AIIdleState.h"
#include"AIJumpState.h"
#include"AIRunState.h"
#include"AIHurtState.h"
void AIStateMachine::Update()
{
	currState->OnUpdate();
}

AIStateMachine::AIStateMachine(ControllerComponent* controllerComponent):StateMachine(controllerComponent)
{
    aiControllerComponent = dynamic_cast<AIControllerComponent*>(controllerComponent);
	stateMap["AttackState"] = std::make_unique<AIAttackState>(this);
	stateMap["IdleState"] = std::make_unique<AIIdleState>(this);
	stateMap["RunState"] = std::make_unique<AIRunState>(this);
	stateMap["JumpState"] = std::make_unique<AIJumpState>(this);
	stateMap["HurtState"] = std::make_unique<AIHurtState>(this);
}

StateMachine* AIStateMachine::Clone(ControllerComponent* controllerComponent)
{
	AIStateMachine* _clone = new AIStateMachine(controllerComponent);
	_clone->currState = nullptr;
	return _clone;
}
