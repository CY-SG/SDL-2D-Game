#include "SDLWindow.h"
#include"SDL2/SDL.h"
#include<iostream>
SDLWindow::SDLWindow(int w, int h, const std::string& name)
{
    window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cout << "SDL´°¿Ú´´½¨Ê§°Ü:" << SDL_GetError() << std::endl;
    }
}

SDLWindow::~SDLWindow()
{
    if (window)
        SDL_DestroyWindow(window);
}

bool SDLWindow::ShouldClose() const
{
    return shouldClose;
}

void SDLWindow::PollEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            shouldClose = true;
        }
    }
}

SDL_Window* SDLWindow::GetSDLWindow()
{
    if (window)return window;
    return nullptr;
}
