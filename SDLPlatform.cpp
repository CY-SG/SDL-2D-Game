#include "SDLPlatform.h"
#include <iostream>
#include <string>
#include"SDL2/SDL_image.h"
bool SDLPlatform::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        std::cout << "SDL初始化错误:" << SDL_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
        std::cout << "SDL_IMAGE初始化错误: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SDLPlatform::ShutDown()
{
    SDL_Quit();
    return true;
}
