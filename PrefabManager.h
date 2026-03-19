#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include"Entity.h"
class ResourceManager;
class AnimationClipManager;
class PrefabManager {
public:
	std::unique_ptr<Entity> GetPrefab(const std::string& name);
	PrefabManager();
	void Initial(ResourceManager* resourceManager, AnimationClipManager* animationClipManager);
private:
	void LoadPlayerPrefab();
	void LoadWall();
	void LoadItems();
	void LoadSensor();
	std::unordered_map<std::string, std::unique_ptr<Entity>>PrefabMap;
	ResourceManager* resourceManager;
	AnimationClipManager* animationClipManager;
};
