#include "ControllerComponent.h"
#include"MoveComponent.h"
#include"JumpComponent.h"
#include"Entity.h"
#include"RigidBody2DComponent.h"
#include"AnimationComponent.h"
#include"InputComponent.h"
void ControllerComponent::Update()
{

}

ControllerComponent::ControllerComponent(Entity* entity)
{
	SetOwner(entity);
	animationComponent = entity->GetComponent<AnimationComponent>();
	rigidBody2DComponent = entity->GetComponent<RigidBody2DComponent>();
	inputComponent = entity->GetComponent<InputComponent>();
}


void ControllerComponent::SetXSpeed(bool MoveLeft)
{
	MoveComponent* moveComponent = owner->GetComponent<MoveComponent>();
	if (MoveLeft)
		rigidBody2DComponent->velocity.x = -moveComponent->Xspeed;
	else rigidBody2DComponent->velocity.x = moveComponent->Xspeed;
}

void ControllerComponent::SetYSpeed()
{
	JumpComponent* jumpComponent = owner->GetComponent<JumpComponent>();
}

void ControllerComponent::SetXSpeed(float Xspeed)
{
	rigidBody2DComponent->velocity.x = Xspeed;
}
