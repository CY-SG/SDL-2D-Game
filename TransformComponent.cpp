#include "TransformComponent.h"
#include"Entity.h"
std::unique_ptr<Component> TransformComponent::Clone(Entity* entity)
{
	std::unique_ptr<TransformComponent>_clone = std::make_unique<TransformComponent>(entity);
	_clone.get()->pos = pos;
	_clone.get()->worldpos = Vec2(0.0f,0.0f);
	_clone.get()->parent = nullptr;
	return std::move(_clone);
}

TransformComponent::TransformComponent(Entity* entity, Entity* parent)
{
	SetOwner(entity);
	pos = Vec2(0.0f, 0.0f);
	worldpos = Vec2(0.0f, 0.0f);
	if(parent!=nullptr)
	this->parent = parent->GetComponent<TransformComponent>();
}

void TransformComponent::Update()
{
	UpdateTransform();
}

void TransformComponent::UpdateTransform()
{
	if (parent == nullptr) {
		worldpos = pos;
	}
	else {
		worldpos = pos + parent->worldpos;
	}
}
