#pragma once
class Input {
public:
	bool Attack = false;
	bool MoveLeft = false;
	bool MoveRight = false;
	bool JumpStart = false;
	bool JumpIng = false;
	bool JumpEnd = false;
	bool Up = false;
	bool Down = false;

	virtual void Update() = 0;
	virtual Input* Clone() = 0;
};