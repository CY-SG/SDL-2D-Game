#include "SDLRender.h"
#include"SDLWindow.h"
#include"SDL2/SDL.h"
#include<iostream>
#include"SDLTexture.h"
#include"Sprite.h"
SDLRender::SDLRender(SDLWindow* window)
{
    renderer = SDL_CreateRenderer(
        window->GetSDLWindow(),
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        std::cout << "SDLRender´´½¨Ê§°Ü:" << SDL_GetError() << std::endl;
    }
}

SDLRender::~SDLRender()
{
    if (renderer)SDL_DestroyRenderer(renderer);
}

void SDLRender::BeginFrame()
{
}

void SDLRender::Clear()
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
}

void SDLRender::EndFrame()
{
    SDL_RenderPresent(renderer);
}

void SDLRender::DrawTexture(Texture* texture, const Rect& src, const Rect& dst)
{
    SDL_Rect SDL_src = ToSDLRect(src);
    SDL_Rect SDL_dst = ToSDLRect(dst);
    SDLTexture* SDLtexture = static_cast<SDLTexture*>(texture);
    SDL_RenderCopy(renderer, static_cast<SDL_Texture*>(SDLtexture->GetTexture()), &SDL_src, &SDL_dst);
}

void SDLRender::DrawSprite(const Sprite* sprite, int x, int y, float scale, bool IsRight)
{
    SDL_RendererFlip flip = IsRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    const Rect& src = sprite->GetRect();
    SDLTexture* SDLtexture = static_cast<SDLTexture*>(sprite->GetTexture());
    Rect dst(x - src.w * 0.5f * scale, y - src.h * 0.5f * scale, src.w * scale, src.h * scale);
    SDL_Rect SDL_src = ToSDLRect(src);
    SDL_Rect SDL_dst = ToSDLRect(dst);
    SDL_RenderCopyEx(
        renderer,
        static_cast<SDL_Texture*>(SDLtexture->GetTexture()),
        &SDL_src,
        &SDL_dst,
        0.0,
        nullptr,
        flip
    );
}

void SDLRender::DrawRect(int pos_x, int pos_y, int size_x, int size_y, color rectcolor)
{
    if (rectcolor == color::Red)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    else if (rectcolor == color::Green)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    else if (rectcolor == color::Blue)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    else if (rectcolor == color::Yellow)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    SDL_Rect rect;
    rect.x = pos_x - size_x * 0.5f;
    rect.y = pos_y - size_y * 0.5f;
    rect.w = size_x;
    rect.h = size_y;

    SDL_RenderDrawRect(renderer, &rect);
}

void SDLRender::DrawLine(int start_x, int start_y, int end_x, int end_y, color linecolor)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderDrawLine(renderer, start_x, start_y, end_x, end_y);
}

void* SDLRender::GetRenderer()
{
    return renderer;
}

SDL_Rect SDLRender::ToSDLRect(const Rect& rect)
{
    SDL_Rect temp;
    temp.x = rect.x;
    temp.y = rect.y;
    temp.w = rect.w;
    temp.h = rect.h;
    return temp;
}
