#include "TransformSystem.h"
#include"Entity.h"
#include"Scene.h"
#include"TransformComponent.h"
#include"World.h"
TransformSystem::TransformSystem()
{
}


void TransformSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		TransformComponent* transformComponent = entity->GetComponent<TransformComponent>();
		if (transformComponent)transformComponent->Update();
	}
}
