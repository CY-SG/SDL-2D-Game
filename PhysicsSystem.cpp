#include "PhysicsSystem.h"
#include"RigidBody2DComponent.h"
#include"Collider2DComponent.h"
#include"TransformComponent.h"
#include"Entity.h"
#include"EngineTime.h"
#include<iostream>
#include"Scene.h"
#include"World.h"
void PhysicsSystem::Update()
{
	ApplyGravity();
	ApplyTransform();
	UpdateTransform();
	CheckCollider();
	HandleInfo();
}

void PhysicsSystem::ApplyGravity()
{
	auto& entities = World::Instance()->entities;
	for (auto& p : entities) {
		TransformComponent* transformComponent = p->GetComponent<TransformComponent>();
		RigidBody2DComponent* rigidBody2DComponent = p->GetComponent<RigidBody2DComponent>();
		if (!rigidBody2DComponent)continue;
		rigidBody2DComponent->collideContact.clear();
		if (rigidBody2DComponent->useGravity)rigidBody2DComponent->velocity = rigidBody2DComponent->velocity + Vec2(0, 5) * rigidBody2DComponent->gravityScale * EngineTime::deltaTime();
	}
}

void PhysicsSystem::ApplyTransform()
{
	auto& entities = World::Instance()->entities;
	for (auto& p : entities) {
		TransformComponent* transformComponent = p->GetComponent<TransformComponent>();
		RigidBody2DComponent* rigidBody2DComponent = p->GetComponent<RigidBody2DComponent>();
		if (!rigidBody2DComponent)continue;
		transformComponent->pos = transformComponent->pos + rigidBody2DComponent->velocity * EngineTime::deltaTime();
	}
}

void PhysicsSystem::CheckCollider()
{
	auto& entites = World::Instance()->entities;
	int size = entites.size();
	for (int i = 0; i < size;i++) {
		auto& p = entites[i];
		TransformComponent* transformComponent = p->GetComponent<TransformComponent>();
		Collider2DComponent* collider2DComponent = p->GetComponent<Collider2DComponent>();
		if (!collider2DComponent)continue;
		for (int j = i + 1; j < size;j++) {
			auto& t = entites[j];
			Collider2DComponent* collider2DComponent_t = t->GetComponent<Collider2DComponent>();
			TransformComponent* transformComponent_t = t->GetComponent<TransformComponent>();
			if (!collider2DComponent_t)continue;
			if (CheckLayer(collider2DComponent,collider2DComponent_t)&&ColliderAABB(transformComponent->worldpos+collider2DComponent->offset, collider2DComponent->size, transformComponent_t->worldpos+collider2DComponent_t->offset, collider2DComponent_t->size)) {
				ResolveCollision(p, t);
			}
		}
	}
}

bool PhysicsSystem::ColliderAABB(const Vec2& apos, const Vec2& asize, const Vec2& bpos, const Vec2& bsize)
{
	return !(apos.x + asize.x * 0.5f < bpos.x - bsize.x * 0.5f || bpos.x + bsize.x * 0.5f < apos.x - asize.x * 0.5f || apos.y + asize.y * 0.5f < bpos.y - bsize.y * 0.5f || bpos.y + bsize.y * 0.5f < apos.y - asize.y * 0.5f);
}

bool PhysicsSystem::CheckLayer(Collider2DComponent* colliderA, Collider2DComponent* colliderB)
{
	return (colliderA->layer & colliderB->mask) && (colliderB->layer & colliderA->mask);
}



void PhysicsSystem::ResolveCollision(Entity* entityA, Entity* entityB)
{
	TransformComponent* transformComponentA = entityA->GetComponent<TransformComponent>();
	TransformComponent* transformComponentB = entityB->GetComponent<TransformComponent>();
	Collider2DComponent* collider2DComponentA = entityA->GetComponent<Collider2DComponent>();
	Collider2DComponent* collider2DComponentB = entityB->GetComponent<Collider2DComponent>();

	CollisionInfo collisionInfo;
	collisionInfo.a = entityA;
	collisionInfo.b = entityB;
	if (collider2DComponentA->IsTrigger || collider2DComponentB->IsTrigger) {
		collisionInfo.IsTrigger = true;
		collisionInfo.normal = Vec2(0, 0);
		collisionInfo.penetration = 0.0f;
	}
	else {
		collisionInfo.IsTrigger = false;
		float ax1 = transformComponentA->worldpos.x + collider2DComponentA->offset.x - collider2DComponentA->size.x * 0.5f;
		float ay1 = transformComponentA->worldpos.y + collider2DComponentA->offset.y - collider2DComponentA->size.y * 0.5f;
		float ax2 = ax1 + collider2DComponentA->size.x;
		float ay2 = ay1 + collider2DComponentA->size.y;

		float bx1 = transformComponentB->worldpos.x + collider2DComponentB->offset.x - collider2DComponentB->size.x * 0.5f;
		float by1 = transformComponentB->worldpos.y + collider2DComponentB->offset.y - collider2DComponentB->size.y * 0.5f;
		float bx2 = bx1 + collider2DComponentB->size.x;
		float by2 = by1 + collider2DComponentB->size.y; 

		float overlapX = std::min(ax2, bx2) - std::max(ax1, bx1);
		float overlapY = std::min(ay2, by2) - std::max(ay1, by1);

		Vec2 Apos = transformComponentA->worldpos + collider2DComponentA->offset;
		Vec2 Bpos = transformComponentB->worldpos + collider2DComponentB->offset;

		float differX = Apos.x - Bpos.x;
		float differY = Apos.y - Bpos.y;

		//处理横向碰撞
		if (overlapX < overlapY) {
			collisionInfo.penetration = overlapX;
			collisionInfo.normal = differX > 0 ? Vec2(1, 0) : Vec2(-1,0);
		}
		//处理纵向碰撞
		else {
			collisionInfo.penetration = overlapY;
			collisionInfo.normal = differY > 0 ? Vec2(0, 1) : Vec2(0, -1);
		}
	}
	collisionInfoes.push_back(collisionInfo);
}

void PhysicsSystem::UpdateTransform()
{
	auto& entites = World::Instance()->entities;
	int size = entites.size();
	for (auto& t : entites) {
		t->GetComponent<TransformComponent>()->Update();
	}
}

void PhysicsSystem::HandleInfo()
{
	for (auto& p : collisionInfoes) {
		Collider2DComponent* ColliderA = p.a->GetComponent<Collider2DComponent>();
		Collider2DComponent* ColliderB = p.b->GetComponent<Collider2DComponent>();
		TransformComponent* TransformA = p.a->GetComponent<TransformComponent>();
		TransformComponent* TransformB = p.b->GetComponent<TransformComponent>();
		RigidBody2DComponent* RigidA = p.a->GetComponent<RigidBody2DComponent>();
		RigidBody2DComponent* RigidB = p.b->GetComponent<RigidBody2DComponent>();
		if (p.IsTrigger) {
			if (ColliderA->onTrigger)ColliderA->onTrigger(p.a, p.b);
			if (ColliderB->onTrigger)ColliderB->onTrigger(p.b, p.a);
		}
		else {
			//位置修正
			Vec2 dis = p.normal * p.penetration;
			if (RigidA && !RigidB)TransformA->pos = TransformA->pos + dis;
			else if (!RigidA && RigidB)TransformB->pos = TransformB->pos - dis;
			else if (RigidA && RigidB) {
				TransformA->pos = TransformA->pos + dis * 0.5;
				TransformB->pos = TransformB->pos - dis * 0.5;
			}
			//速度修正
			if (p.normal.x != 0)
			{
				if(RigidA)
				RigidA->velocity.x = 0;
				if (RigidB)
				RigidB->velocity.x = 0;
			}
			else
			{
				if(RigidA)
				RigidA->velocity.y = 0;
				if (RigidB)
				RigidB->velocity.y = 0;
			}

			if (RigidA)RigidA->collideContact.push_back(CollideContact{ p.b,p.normal });
			if (RigidB)RigidB->collideContact.push_back(CollideContact{ p.a,p.normal*-1 });
			//事件触发
			if (ColliderA->onCollision)ColliderA->onCollision(p.a, p.b);
			if (ColliderB->onCollision)ColliderB->onCollision(p.b, p.a);
		}
	}
	collisionInfoes.clear();
}

