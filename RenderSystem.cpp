#include "RenderSystem.h"
#include"AnimationComponent.h"
#include"Entity.h"
#include"Camera2D.h"
#include"TransformComponent.h"
#include"Collider2DComponent.h"
#include"Render.h"
#include"Scene.h"
#include"World.h"
void RenderSystem::Update()
{
	auto& entities = World::Instance()->entities;
	//更新图片
	

	//更新动画
	for (auto& entity : entities) {
		auto transform = entity->GetComponent<TransformComponent>();
		Vec2 pos = transform->worldpos;
		AnimationComponent* animationComponent = entity->GetComponent<AnimationComponent>();
		if(animationComponent)animationComponent->RenderAnimationWithCamera(render, camera, pos.x, pos.y);
	}

	//Debug模式
	//if (DebugMode) {
	//	RenderPhysics(scene);
	//}
}


RenderSystem::RenderSystem(Render* render,Camera2D* camera)
{
	this->render = render;
	this->camera = camera;
}

void RenderSystem::RenderPhysics()
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
