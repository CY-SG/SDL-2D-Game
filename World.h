#pragma once
#include<vector>
#include<memory>
#include"Camera2D.h"
#include"Render.h"
#include"AnimationClipManager.h"
#include"ResourceManager.h"
#include"PrefabManager.h"
#include"SceneManager.h"
#include"System.h"
#include"SceneData.h"
class CameraSystem;
class World {
public:
	static World* Instance();
	void Update();
	PrefabManager* GetPrefabManager();
	SceneManager* GetSceneManager();
	void Initial(std::unique_ptr<Render>renderer,std::unique_ptr<Camera2D>camera2D,std::unique_ptr<ResourceManager> resourceManager, std::unique_ptr<AnimationClipManager> animationClipManager);
	const std::vector<std::unique_ptr<System>>& GetSystems()const;
	CameraSystem* GetCameraSystem()const;
	Entity* Instantiate(const std::string& name);
	Entity* Instantiate(const std::string& name,Entity*parent);
	void DestroyEntityByScene(Entity* entity);
	void DestroyEntity(Entity* entity);
	std::vector<std::unique_ptr<Entity>>roots;
	std::vector<std::pair<Entity*, std::unique_ptr<Entity>>>toAddentities;

	std::vector<Entity*>entities;
	SceneCoord persitentCoord = { 0,0 };

	std::unordered_map<int, EntityState>sceneState;

private:
	void RemoveEntity();
	void AddRootEntity(std::unique_ptr<Entity>entity);
	void AddChildEntity(Entity* parent, std::unique_ptr<Entity>child);
	void FlushAdd();
	void HandleHierarchy();
	void Traverse(Entity* root);
	void RemoveChild(Entity* root);

	void WorldUpdate();

	static World* instance;
	std::unique_ptr<PrefabManager> prefabManager;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<AnimationClipManager> animationClipManager;
	std::vector<std::unique_ptr<System>>systems;
	std::unique_ptr<Render>renderer;
	std::unique_ptr<Camera2D>camera2D;
	std::unique_ptr<CameraSystem>cameraSystem;
};