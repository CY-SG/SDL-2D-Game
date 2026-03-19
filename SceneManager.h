#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include"SceneData.h"
#include"Scene.h"
#include<unordered_set>
#include"Math.h"
class Entity;
class SceneManager {
public:
	SceneManager();
	//void RemoveEntity();
	Scene* GetCurrScene();

	void UpdateStreaming();
	void LoadScene(SceneCoord coord);
	void SetTarget(Entity* entity);
	void InitLoad(SceneCoord coord);
private:

	SceneCoord GetSceneFromPos(Vec2 pos);

	void UnloadScene(SceneCoord coord);

	SceneData GetSceneData(SceneCoord coord);

	void InitSceneData();

	std::unordered_map<SceneCoord, SceneData, SceneCoordHash>SceneDataMap;
	std::unordered_map<SceneCoord, SceneChunk, SceneCoordHash>SceneChunkMap;
	Scene* currScene;
	SceneCoord currSceneCoord{ 99999,99999 };
	int chunkSize = 2000;
	Entity* streamingTarget = nullptr;
};