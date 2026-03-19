#include "InputComponent.h"
#include"Input.h"
InputComponent::InputComponent(Entity* entity, Input* input)
{
	SetOwner(entity);
	this->input = input;
}

InputComponent::InputComponent(Entity* entity)
{
	SetOwner(entity);
}

std::unique_ptr<Component> InputComponent::Clone(Entity* entity)
{
	std::unique_ptr<InputComponent>_clone = std::make_unique<InputComponent>(entity);
	_clone.get()->input = this->input->Clone();
	return std::move(_clone);
}

void InputComponent::Update()
{
	input->Update();
}
