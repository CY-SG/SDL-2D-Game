#include "InputSystem.h"
#include"Entity.h"
#include"InputComponent.h"
#include"Scene.h"
#include"World.h"
InputSystem::InputSystem()
{
}

void InputSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		InputComponent* inputComponent = entity->GetComponent<InputComponent>();
		if (inputComponent)inputComponent->Update();
	}
}

