#pragma once
#include"Render.h"
class StateMachine;
class BaseState {
public:
	BaseState(StateMachine* _stateMachine);
	virtual ~BaseState() = default;
	virtual void OnEnter() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
	virtual BaseState* Clone(StateMachine*_stateMachine) = 0;
	color _color;
protected:
	StateMachine* stateMachine;
};