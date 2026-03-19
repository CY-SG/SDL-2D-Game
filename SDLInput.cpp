#include "SDLInput.h"
#include"SDL2/SDL.h"
void SDLInput::Update()
{
	const Uint8* SDL_keyboard = SDL_GetKeyboardState(nullptr);

	Attack_KeyPressed = SDL_keyboard[SDL_SCANCODE_J];
	Left_KeyPressed = SDL_keyboard[SDL_SCANCODE_A];
	Right_KeyPressed = SDL_keyboard[SDL_SCANCODE_D];
	Up_KeyPressed = SDL_keyboard[SDL_SCANCODE_W];
	Down_KeyPressed = SDL_keyboard[SDL_SCANCODE_S];
	Jump_KeyPressed = SDL_keyboard[SDL_SCANCODE_K];

	Attack_KeyDown = Attack_KeyPressed && !Pre_Attack_Key;
	Attack_KeyUp = !Attack_KeyPressed && Pre_Attack_Key;

	Left_KeyDown = Left_KeyPressed && !Pre_Left_Key;
	Left_KeyUp = !Left_KeyPressed && Pre_Left_Key;

	Right_KeyDown = Right_KeyPressed && !Pre_Right_Key;
	Right_KeyUp = !Right_KeyPressed && Pre_Right_Key;

	Up_KeyDown = Up_KeyPressed && !Pre_Up_Key;
	Up_KeyUp = !Up_KeyPressed && Pre_Up_Key;

	Down_KeyDown = Down_KeyPressed && !Pre_Down_Key;
	Down_KeyUp = !Down_KeyPressed && Pre_Down_Key;

	Jump_KeyDown = Jump_KeyPressed && !Pre_Jump_Key;
	Jump_KeyUp = !Jump_KeyPressed && Pre_Jump_Key;

	Pre_Attack_Key = Attack_KeyPressed;
	Pre_Left_Key = Left_KeyPressed;
	Pre_Right_Key = Right_KeyPressed;
	Pre_Up_Key = Up_KeyPressed;
	Pre_Down_Key = Down_KeyPressed;
	Pre_Jump_Key = Jump_KeyPressed;

	Attack = Attack_KeyDown;
	MoveLeft = Left_KeyPressed;
	MoveRight = Right_KeyPressed;
	JumpStart = Jump_KeyDown;
	JumpIng = Jump_KeyPressed;
	JumpEnd = Jump_KeyUp;
	Up = Up_KeyPressed;
	Down = Down_KeyPressed;
}

Input* SDLInput::Clone()
{
	return new SDLInput();
}
