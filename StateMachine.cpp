#include "StateMachine.h"
#include"BaseState.h"
#include"AnimationComponent.h"
StateMachine::StateMachine(ControllerComponent* controllerComponent):controllerComponent(controllerComponent)
{

}
void StateMachine::ChangeToState(const std::string& name)
{
	BaseState* state = stateMap[name].get();
	if (state == currState)return;
	currState->OnExit();
	currState = state;
	currState->OnEnter();
}

void StateMachine::AddState(const std::string& name, std::unique_ptr<BaseState> state)
{
	stateMap[name] = std::move(state);
}

void StateMachine::SetStartState(const std::string& name)
{
	currState = stateMap[name].get();
	currState->OnEnter();
}

BaseState* StateMachine::GetCurrState()
{
	return currState;
}

void StateMachine::Update()
{
	currState->OnUpdate();
}
