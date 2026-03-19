#include "SDLResourceManager.h"
#include"SDLRender.h"
#include"SDLTexture.h"
#include<iostream>
SDLResourceManager::SDLResourceManager(SDLRender* renderer)
{
    this->renderer = renderer;
}

std::shared_ptr<Texture> SDLResourceManager::LoadTexture(const std::string& path)
{
    if (textureMap.count(path))return textureMap[path];
    std::shared_ptr<SDLTexture> texture = std::make_shared<SDLTexture>(static_cast<SDL_Renderer*>(renderer->GetRenderer()), path);
    textureMap[path] = texture;
    return texture;
}
