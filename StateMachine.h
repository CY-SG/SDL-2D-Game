#pragma once
#include<unordered_map>
#include<string>
#include<memory>
class BaseState;
class ControllerComponent;
class StateMachine {
public:
	StateMachine(ControllerComponent* controllerComponent);
	void ChangeToState(const std::string& name);
	void AddState(const std::string& name, std::unique_ptr<BaseState> state);
	void SetStartState(const std::string& name);
	BaseState* GetCurrState();
	virtual void Update();
	virtual ~StateMachine() = default;
	virtual StateMachine* Clone(ControllerComponent* controllerComponent) = 0;
	ControllerComponent* controllerComponent;
protected:
	std::unordered_map<std::string, std::unique_ptr<BaseState>>stateMap;
	BaseState* currState;
};