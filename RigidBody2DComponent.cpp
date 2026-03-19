#include "RigidBody2DComponent.h"

RigidBody2DComponent::RigidBody2DComponent(Entity* entity)
{
	SetOwner(entity);
	useGravity = true;;
	gravityScale = 0.3f;
	velocity = Vec2(0, 0);
}

std::unique_ptr<Component> RigidBody2DComponent::Clone(Entity* entity)
{
	std::unique_ptr<RigidBody2DComponent>_clone = std::make_unique<RigidBody2DComponent>(entity);
	_clone.get()->gravityScale = gravityScale;
	_clone.get()->useGravity = useGravity;
	_clone.get()->velocity = velocity;
	_clone.get()->collideContact.clear();
	return std::move(_clone);
}

void RigidBody2DComponent::Update()
{
}
