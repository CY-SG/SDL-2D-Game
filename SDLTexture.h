#pragma once
#include"Texture.h"
#include<string>
class SDL_Texture;
class SDL_Renderer;
class SDLTexture :public Texture {
public:
	SDLTexture(SDL_Renderer* renderer,const std::string& path);
	~SDLTexture();
	void * GetTexture();
private:
	SDL_Texture* texture = nullptr;
};