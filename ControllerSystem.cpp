#include "ControllerSystem.h"
#include"ControllerComponent.h"
#include"Entity.h"
#include"Scene.h"
#include"World.h"
void ControllerSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		ControllerComponent* controllerComponent = entity->GetComponent<ControllerComponent>();
		if (controllerComponent)controllerComponent->Update();
	}

}


ControllerSystem::ControllerSystem()
{
}
