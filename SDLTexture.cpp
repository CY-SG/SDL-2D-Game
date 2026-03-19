#include "SDLTexture.h"
#include"SDL2/SDL.h"
#include"SDL2/SDL_image.h"
#include<string>
#include <stdexcept>
#include<iostream>
SDLTexture::SDLTexture(SDL_Renderer* renderer, const std::string& path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface) {
		throw std::runtime_error("º”‘ÿÕº∆¨ in CPU  ß∞‹: " + path);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
	if (!texture) {
		throw std::runtime_error("º”‘ÿÕº∆¨ in GPU  ß∞‹: " + path);
	}
}

SDLTexture::~SDLTexture()
{
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		height = 0;
		width = 0;
	}
}

void* SDLTexture::GetTexture()
{
	return texture;
}

