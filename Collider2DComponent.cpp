#include "Collider2DComponent.h"

Collider2DComponent::Collider2DComponent(Entity* entity, const Vec2& _size, const Vec2& _offset, PhysicsLayer layer, uint32_t _mask):mask(_mask),layer(layer),size(_size),offset(_offset)
{
	SetOwner(entity);
	onCollision = nullptr;
	onTrigger = nullptr;
	IsTrigger = false;
}

void Collider2DComponent::Update()
{
}

std::unique_ptr<Component> Collider2DComponent::Clone(Entity* entity)
{
	std::unique_ptr<Collider2DComponent>_clone = std::make_unique<Collider2DComponent>(entity,size,offset,layer,mask);
	_clone.get()->onCollision = onCollision;
	_clone.get()->onTrigger = onTrigger;
	_clone.get()->IsTrigger = IsTrigger;
	return std::move(_clone);
}

void Collider2DComponent::SetOnCollision(std::function<void(Entity* entityA, Entity* entityB)> onCollision_event)
{
	onCollision = onCollision_event;
}

void Collider2DComponent::SetOnTrigger(std::function<void(Entity* entityA, Entity* entityB)> onTrigger_event)
{
	onTrigger = onTrigger_event;
}
