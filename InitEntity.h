#pragma once
#include<unordered_map>
#include<string>
class SDLRender;
class ResourceManager;
class AnimationClipManager;
class Entity;
class InitEntity {
public:
	void LoadResource(ResourceManager*resourceManager,AnimationClipManager*animationClipManager);
	Entity* GetEntity(const std::string& name);
private:
	std::unordered_map<std::string, Entity*>EntityMap;
};