#pragma once
#include<unordered_map>
#include <memory>
#include<string>
class Texture;
class ResourceManager {
public:
	virtual ~ResourceManager() = default;
	virtual std::shared_ptr<Texture> LoadTexture(const std::string& path) = 0;
protected:
	std::unordered_map<std::string, std::shared_ptr<Texture>>textureMap;
};