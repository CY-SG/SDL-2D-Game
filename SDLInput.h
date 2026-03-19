#pragma once
#include"Input.h"
class SDLInput :public Input {
public:
	bool Attack_KeyPressed = false;
	bool Left_KeyPressed = false;
	bool Right_KeyPressed = false;
	bool Up_KeyPressed = false;
	bool Down_KeyPressed = false;
	bool Jump_KeyPressed = false;

	bool Attack_KeyDown = false;
	bool Left_KeyDown = false;
	bool Right_KeyDown = false;
	bool Up_KeyDown = false;
	bool Down_KeyDown = false;
	bool Jump_KeyDown = false;

	bool Attack_KeyUp = false;
	bool Left_KeyUp = false;
	bool Right_KeyUp = false;
	bool Up_KeyUp = false;
	bool Down_KeyUp = false;
	bool Jump_KeyUp = false;

	bool Pre_Attack_Key = false;
	bool Pre_Left_Key = false;
	bool Pre_Right_Key = false;
	bool Pre_Up_Key = false;
	bool Pre_Down_Key = false;
	bool Pre_Jump_Key;
	void Update()override;
	Input* Clone()override;
};