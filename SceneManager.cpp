#include "SceneManager.h"
#include"World.h"
#include"PrefabManager.h"
#include"PlayerControllerComponent.h"
#include"AnimationComponent.h"
#include"Collider2DComponent.h"
#include"CameraSystem.h"
#include"AIControllerComponent.h"
#include"TransformComponent.h"
#include"Entity.h"
#include<iostream>
SceneManager::SceneManager()
{
	InitSceneData();
}

//void SceneManager::AddScene(const std::string& name, std::unique_ptr<Scene> scene)
//{
//	SceneMap[name] = std::move(scene);
//}
//
//void SceneManager::LoadScene(const std::string& name)
//{
//	currScene = SceneMap[name].get();
//}

//void SceneManager::RemoveEntity()
//{
//	currScene->RemoveEntity();
//}

Scene* SceneManager::GetCurrScene()
{
	return currScene;
}

void SceneManager::UpdateStreaming()
{
	if (streamingTarget == nullptr)return;
	SceneCoord newScene = GetSceneFromPos(streamingTarget->GetComponent<TransformComponent>()->pos);

	if (newScene == currSceneCoord)
		return;

	currSceneCoord = newScene;
	std::unordered_set<SceneCoord, SceneCoordHash> needed;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			SceneCoord c;

			c.x = newScene.x + dx;
			c.y = newScene.y + dy;

			needed.insert(c);

			if (SceneChunkMap.count(c) == 0)
			{
				LoadScene(c);
			}
		}
	}

	std::vector<SceneCoord> toUnload;

	for (auto& pair : SceneChunkMap)
	{
		SceneCoord c = pair.first;

		if (needed.count(c) == 0)
		{
			toUnload.push_back(c);
		}
	}

	for (auto& c : toUnload)
	{
		UnloadScene(c);
	}
}

//void SceneManager::LoadScene_1()
//{
//	std::unique_ptr<Scene>scene = std::make_unique<Scene>();
//	std::unique_ptr<Entity>player = std::move(World::Instance()->GetPrefabManager()->GetPrefab("Player"));
//	std::unique_ptr<Entity>Wall_1 = std::move(World::Instance()->GetPrefabManager()->GetPrefab("Wall_1"));
//	std::unique_ptr<Entity>Wall_2 = std::move(World::Instance()->GetPrefabManager()->GetPrefab("Wall_2"));
//	std::unique_ptr<Entity>Enemy_1 = std::move(World::Instance()->GetPrefabManager()->GetPrefab("Enemy_1"));
//	PlayerControllerComponent* P_controllerComponent = player->GetComponent<PlayerControllerComponent>();
//	AnimationComponent* P_animationComponent = player->GetComponent<AnimationComponent>();
//	AIControllerComponent* E_controllerComponent = Enemy_1->GetComponent<AIControllerComponent>();
//	P_controllerComponent->SetStateStart(StateType::MoveState, "P_Normal");
//	P_controllerComponent->SetStateStart(StateType::ActionState, "P_None");
//	E_controllerComponent->SetStateStart(AIStateType::Action, "IdleState");
//	E_controllerComponent->SetStateStart(AIStateType::Decision, "IdleState");
//	P_animationComponent->SetStartState("P_Idle", 0);
//	P_animationComponent->SetStartState("P_None", 1);
//
//	CameraSystem* cameraSystem = World::Instance()->GetCameraSystem();
//	cameraSystem->SetFollowBehavior(0.05f, player.get());
//
//	scene.get()->AddRootEntity(std::move(player));
//	scene.get()->AddRootEntity(std::move(Wall_1));
//	scene.get()->AddRootEntity(std::move(Wall_2));
//	scene.get()->AddRootEntity(std::move(Enemy_1));
//	SceneMap["Scene_1"] = std::move(scene);
//
//}

SceneCoord SceneManager::GetSceneFromPos(Vec2 pos)
{
	SceneCoord coord;

	coord.x = (int)floor(pos.x / chunkSize);
	coord.y = (int)floor(pos.y / chunkSize);

	return coord;
}

void SceneManager::LoadScene(SceneCoord coord)
{
	SceneChunk chunk;
	chunk.coord = coord;

	SceneData data = GetSceneData(coord);
	if (data.spawns.size() == 0)return;
	for (auto& spawn : data.spawns)
	{
		if (spawn.id == -1 || World::Instance()->sceneState[spawn.id].IsDead)continue;
		auto entity = World::Instance()->Instantiate(spawn.prefabName);
		World::Instance()->sceneState[spawn.id] = { false,entity };
		auto transform =entity->GetComponent<TransformComponent>();

		transform->pos ={spawn.x,spawn.y};
		entity->id = spawn.id;


		if (spawn.initializer)
			spawn.initializer(entity);
		chunk.spawnedEntities.push_back(spawn.id);
	}

	SceneChunkMap[coord] = std::move(chunk);
}

void SceneManager::SetTarget(Entity* entity)
{
	this->streamingTarget = entity;
}

void SceneManager::InitLoad(SceneCoord coord)
{
	currSceneCoord = coord;
	LoadScene(coord);
}

void SceneManager::UnloadScene(SceneCoord coord)
{
	auto& chunk = SceneChunkMap[coord];

	for (auto& t : chunk.spawnedEntities)
	{
		if (!World::Instance()->sceneState[t].IsDead)
		{
			World::Instance()->DestroyEntityByScene(World::Instance()->sceneState[t].entity);
		}
	}

	SceneChunkMap.erase(coord);
}

SceneData SceneManager::GetSceneData(SceneCoord coord)
{
	if (SceneDataMap.count(coord))return SceneDataMap[coord];
	return SceneData{};
}

void SceneManager::InitSceneData()
{
	SceneData data0_0;
	data0_0.spawns = {
		{ 0, "Player",100.0f,150.0f,[](Entity* entity) {
		PlayerControllerComponent* P_controllerComponent = entity->GetComponent<PlayerControllerComponent>();
		AnimationComponent* P_animationComponent = entity->GetComponent<AnimationComponent>();
		P_controllerComponent->SetStateStart(StateType::MoveState, "P_Normal");
		P_controllerComponent->SetStateStart(StateType::ActionState, "P_None");
		P_animationComponent->SetStartState("P_Idle", 0);
		P_animationComponent->SetStartState("P_None", 1);
		CameraSystem* cameraSystem = World::Instance()->GetCameraSystem();
		cameraSystem->SetFollowBehavior(0.05f, entity);
		World::Instance()->GetSceneManager()->SetTarget(entity);
		World::Instance()->sceneState[0].IsDead = true;
		} },
		{1, "Wall_1",120.0f,300.0f,nullptr},
		{2, "Wall_2",-80.0f,150.0f,nullptr},
		{3, "Enemy_1",300.0f,200.0f,[](Entity* entity) {
			AIControllerComponent* E_controllerComponent = entity->GetComponent<AIControllerComponent>();
			AnimationComponent* E_animationComponent = entity->GetComponent<AnimationComponent>();
			E_controllerComponent->SetStateStart(AIStateType::Action, "IdleState");
			E_controllerComponent->SetStateStart(AIStateType::Decision, "IdleState");
			E_animationComponent->SetStartState("E1_Idle", 0);
		}},
		{4, "Door",190.0f,200.0f,nullptr}
	};
	SceneDataMap[{0, 0}] = data0_0;

	SceneData data2_2;
	data2_2.spawns = {
		{5, "Wall_3",4800.0f,5600.0f,nullptr},
		{6, "Enemy_1",4500.0f,5000.0f,[](Entity* entity) {
			AIControllerComponent* E_controllerComponent = entity->GetComponent<AIControllerComponent>();
			AnimationComponent* E_animationComponent = entity->GetComponent<AnimationComponent>();
			E_controllerComponent->SetStateStart(AIStateType::Action, "IdleState");
			E_controllerComponent->SetStateStart(AIStateType::Decision, "IdleState");
			E_animationComponent->SetStartState("E1_Idle", 0);
		}},
		{7, "Door1",4800.0f,5400.0f,nullptr}
	};
	SceneDataMap[{2, 2}] = data2_2;
}
