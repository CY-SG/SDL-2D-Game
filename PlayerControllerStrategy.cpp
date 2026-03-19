#include "PlayerControllerStrategy.h"
#include"EngineInput.h"
#include"RigidBody2DComponent.h"
#include"MoveComponent.h"
#include"JumpComponent.h"
#include"AnimationComponent.h"
#include"Entity.h"
PlayerControllerStrategy::PlayerControllerStrategy()
{
	actionState = ActionState::None;
}

void PlayerControllerStrategy::Update()
{
}

void PlayerControllerStrategy::UpdateMoveState()
{
	RigidBody2DComponent* rigidComponent = entity->GetComponent<RigidBody2DComponent>();
	AnimationComponent* animationComponent = entity->GetComponent<AnimationComponent>();
	Vec2& speed = rigidComponent->velocity;
	bool IsGround = rigidComponent->IsGround;
	//ÉèÖÃ¶¯»­
	animationComponent->SetBool("IsGround", IsGround, 0);
	animationComponent->SetFloat("Xspeed", abs(speed.x), 0);
	animationComponent->SetFloat("Yspeed", speed.y, 0);
	if (speed.x > 0)animationComponent->SetFlip(true);
	else if (speed.x < 0)animationComponent->SetFlip(false);
}

void PlayerControllerStrategy::HandleInput()
{
	RigidBody2DComponent* rigidComponent = entity->GetComponent<RigidBody2DComponent>();
	MoveComponent* moveComponent = entity->GetComponent<MoveComponent>();
	JumpComponent* jumpComponent = entity->GetComponent<JumpComponent>();
	if (CanMove()) {
		if (EngineInput::GetKeyCode(KeyCode::A))rigidComponent->velocity.x = -moveComponent->Xspeed;
		if (EngineInput::GetKeyCode(KeyCode::D))rigidComponent->velocity.x = moveComponent->Xspeed;
	}
	if (CanJump()) {
		if (EngineInput::GetKeyDown(KeyCode::W))rigidComponent->velocity.y = -jumpComponent->Yspeed;
	}
}

bool PlayerControllerStrategy::CanMove()
{
	return actionState == ActionState::None;
}

bool PlayerControllerStrategy::CanJump()
{
	RigidBody2DComponent* rigidComponent = entity->GetComponent<RigidBody2DComponent>();
	return rigidComponent->IsGround && actionState == ActionState::None;
}
