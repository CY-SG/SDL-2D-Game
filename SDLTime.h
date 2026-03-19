#pragma once
#include"Time.h"
class SDLTime :public Time {
public:
	SDLTime();
	~SDLTime();
	void Tick() override;
	float DeltaTime() override;
	struct NowTime;
	NowTime* nowTimeTemp;
};