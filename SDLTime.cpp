#include "SDLTime.h"
#include"SDL2/SDL.h"
#include<iostream>
struct SDLTime::NowTime {
public:
	Uint64 pretime = 0.0f;
};
SDLTime::SDLTime()
{
	delta = 0.0f;
	nowTimeTemp = new NowTime();
	nowTimeTemp->pretime = SDL_GetPerformanceCounter();
}

SDLTime::~SDLTime()
{
	delta = 0.0f;
	nowTimeTemp->pretime = 0.0f;
}

void SDLTime::Tick()
{
	Uint64 nowtime = SDL_GetPerformanceCounter();
	delta = (nowtime - nowTimeTemp->pretime) / (float)SDL_GetPerformanceFrequency();
	nowTimeTemp->pretime = nowtime;
}

float SDLTime::DeltaTime()
{
	return delta;
}
