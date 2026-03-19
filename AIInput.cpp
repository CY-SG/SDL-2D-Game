#include "AIInput.h"
#include"AIDecisionMachine.h"
AIInput::AIInput()
{
}

void AIInput::Update()
{
	MoveLeft = false;
	MoveRight = false;
	Attack = false;
	JumpStart = false;
	Up = false;
	Down = false;
}

Input* AIInput::Clone()
{
	AIInput* _clone = new AIInput();
	return _clone;
}
