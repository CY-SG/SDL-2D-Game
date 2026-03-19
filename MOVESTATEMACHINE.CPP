#include "MoveStateMachine.h"
#include"ControllerComponent.h"
#include"PlayerControllerComponent.h"
#include"BaseState.h"
void MoveStateMachine::Update()
{
	currState->OnUpdate();
}

StateMachine* MoveStateMachine::Clone(ControllerComponent* controllerComponent)
{
	MoveStateMachine* _clone = new MoveStateMachine(controllerComponent);
	_clone->currState = nullptr;
	for (auto& p : stateMap) {
		_clone->AddState(p.first, std::move(std::unique_ptr<BaseState>(p.second.get()->Clone(_clone))));
	}
	return _clone;
}

MoveStateMachine::MoveStateMachine(ControllerComponent* controllerComponent):StateMachine(controllerComponent)
{
	playerControllerComponent = dynamic_cast<PlayerControllerComponent*>(controllerComponent);
}
