#pragma once
#include"ResourceManager.h"
class SDLRender;
class SDLResourceManager :public ResourceManager {
public:
	SDLResourceManager(SDLRender* renderer);
	std::shared_ptr<Texture> LoadTexture(const std::string& path) override;
private:
	SDLRender* renderer;
};