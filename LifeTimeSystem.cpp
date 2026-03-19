#include "LifeTimeSystem.h"
#include"Scene.h"
#include"Entity.h"
#include"LifeTimeComponent.h"
#include"World.h"
void LifeTimeSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		LifeTimeComponent* lifeTimeComponent = entity->GetComponent<LifeTimeComponent>();
		if (lifeTimeComponent)lifeTimeComponent->Update();
	}
}


LifeTimeSystem::LifeTimeSystem()
{
}
