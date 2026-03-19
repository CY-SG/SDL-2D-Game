#include "DamageSystem.h"
#include"Entity.h"
#include"Scene.h"
#include"DamageComponent.h"
#include"World.h"
void DamageSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		DamageComponent* damageComponent = entity->GetComponent<DamageComponent>();
		if (damageComponent)damageComponent->Update();
	}
}

DamageSystem::DamageSystem()
{
}
