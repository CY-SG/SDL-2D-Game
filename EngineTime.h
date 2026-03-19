#pragma once
#include"Time.h"
class EngineTime {
public:
	static void Init(Time* time);
	static float deltaTime();
	static void Tick();
private:
	static Time* instance;
};