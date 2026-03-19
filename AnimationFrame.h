#pragma once
#include"Sprite.h"
struct AnimationFrame {
public:
	Sprite sprite;
	float duration;
	AnimationFrame(const Sprite& sprite,float duration):sprite(sprite),duration(duration){}
};