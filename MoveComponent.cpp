#include "MoveComponent.h"

MoveComponent::MoveComponent(Entity* entity, float speed) :Xspeed(speed)
{
	SetOwner(entity);
}

MoveComponent::MoveComponent(Entity* entity)
{
	SetOwner(entity);
}

void MoveComponent::Update()
{
}

std::unique_ptr<Component> MoveComponent::Clone(Entity* entity)
{
	std::unique_ptr<MoveComponent>_clone = std::make_unique<MoveComponent>(entity);
	_clone.get()->Xspeed = Xspeed;
	return std::move(_clone);
}
