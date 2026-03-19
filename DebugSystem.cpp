#include "DebugSystem.h"
#include"EngineTime.h"
#include"BaseState.h"
#include"AIControllerComponent.h"
#include"AIDecisionMachine.h"
#include"Scene.h"
#include"Entity.h"
#include"Collider2DComponent.h"
#include"TransformComponent.h"
#include"Camera2D.h"
#include"Render.h"
#include<iostream>
#include"World.h"
DebugSystem::DebugSystem(Render* render, Camera2D* camera)
{
	this->render = render;
	this->camera = camera;
}

void DebugSystem::Update()
{
	currTime += EngineTime::deltaTime();
	frameCount++;
	if (currTime >= 0.5f) {
		std::cout << "µ±Ç°FPS£º" << (float)frameCount / currTime << std::endl;
		currTime = 0.0f;
		frameCount = 0;
	}

	RenderPhysics();
	RenderAIState();
}

void DebugSystem::RenderPhysics()
{
	auto& entities = World::Instance()->entities;
	for (auto& entity : entities) {
		Collider2DComponent* collider = entity->GetComponent<Collider2DComponent>();
		TransformComponent* transform = entity->GetComponent<TransformComponent>();
		if (collider) {
			Vec2 pos = camera->WorldToScreen(transform->worldpos + collider->offset);
			color _color = color::Red;
			if (collider->IsTrigger)_color = color::Green;
			render->DrawRect(pos.x, pos.y, collider->size.x, collider->size.y, _color);
		}
	}
}

void DebugSystem::RenderAIState()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		AIControllerComponent* controllerComponent = entity->GetComponent<AIControllerComponent>();
		if (!controllerComponent)continue;
		Collider2DComponent* collider = entity->GetComponent<Collider2DComponent>();
		TransformComponent* transform = entity->GetComponent<TransformComponent>();
		Vec2 pos = camera->WorldToScreen(transform->worldpos + collider->offset);
		BaseState* state = controllerComponent->aiDecStateMachine.get()->GetCurrState();
		render->DrawRect(pos.x, pos.y, collider->size.x / 2, collider->size.y / 2, state->_color);
	}
}
