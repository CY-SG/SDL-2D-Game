#include "AnimationSystem.h"
#include"Entity.h"
#include"AnimationComponent.h"
#include"Scene.h"
#include"World.h"
AnimationSystem::AnimationSystem()
{
}

void AnimationSystem::Update()
{
	auto& entities = World::Instance()->entities;

	for (auto& entity : entities) {
		AnimationComponent* animationComponent = entity->GetComponent<AnimationComponent>();
		if (animationComponent)animationComponent->Update();
	}
}

