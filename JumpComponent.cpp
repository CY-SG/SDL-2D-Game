#include "JumpComponent.h"

JumpComponent::JumpComponent(Entity* entity, int jumpCount, std::vector<JumpState>& jumpState):jumpCount(jumpCount)
{
	SetOwner(entity);
	this->jumpStates = jumpState;
}

JumpComponent::JumpComponent(Entity* entity)
{
	SetOwner(entity);
}

void JumpComponent::Update()
{
}

std::unique_ptr<Component> JumpComponent::Clone(Entity* entity)
{
	std::unique_ptr<JumpComponent>_clone = std::make_unique<JumpComponent>(entity);
	_clone.get()->jumpCount = jumpCount;
	_clone.get()->jumpStates = jumpStates;
	return std::move(_clone);
}
