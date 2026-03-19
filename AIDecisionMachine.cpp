#include "AIDecisionMachine.h"
#include"ControllerComponent.h"
#include"AIControllerComponent.h"
#include"AIDec_ChaseState.h"
#include"AIDec_IdleState.h"
#include"AIDec_PatrolState.h"
#include"AIDec_AttackState.h"
void AIDecisionMachine::Update()
{
	currState->OnUpdate();
}


AIDecisionMachine::AIDecisionMachine(ControllerComponent* controllerComponent):StateMachine(controllerComponent)
{
	aiControllerComponent = dynamic_cast<AIControllerComponent*>(controllerComponent);
	stateMap["PatrolState"] = std::make_unique<AIDec_PatrolState>(this);
	stateMap["IdleState"] = std::make_unique<AIDec_IdleState>(this);
	stateMap["ChaseState"] = std::make_unique<AIDec_ChaseState>(this);
	stateMap["AttackState"] = std::make_unique<AIDec_AttackState>(this);
}

StateMachine* AIDecisionMachine::Clone(ControllerComponent* controllerComponent)
{
	AIDecisionMachine* _clone = new AIDecisionMachine(controllerComponent);
	_clone->currState = nullptr;
	return _clone;
}
