#include "ActionStateMachine.h"
#include"ControllerComponent.h"
#include"PlayerControllerComponent.h"
#include"BaseState.h"
void ActionStateMachine::Update()
{
	currState->OnUpdate();
}

StateMachine* ActionStateMachine::Clone(ControllerComponent* controllerComponent)
{
	ActionStateMachine* _clone = new ActionStateMachine(controllerComponent);
	_clone->currState = nullptr;
	for (auto& p : stateMap) {
		_clone->AddState(p.first, std::move(std::unique_ptr<BaseState>(p.second.get()->Clone(_clone))));
	}
	return _clone;
}

ActionStateMachine::ActionStateMachine(ControllerComponent* controllerComponent):StateMachine(controllerComponent)
{
	playerControllerComponent = dynamic_cast<PlayerControllerComponent*>(controllerComponent);
}
