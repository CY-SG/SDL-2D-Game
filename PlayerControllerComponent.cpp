#include "PlayerControllerComponent.h"
#include"ControllerComponent.h"
#include"MoveComponent.h"
#include"JumpComponent.h"
#include"MoveStateMachine.h"
#include"StateMachine.h"
#include"Entity.h"
#include"EngineTime.h"
#include"RigidBody2DComponent.h"
#include"Collider2DComponent.h"
#include"AnimationComponent.h"
#include"TransformComponent.h"
#include"ActionStateMachine.h"
#include"PrefabManager.h"
#include"BaseState.h"
#include"CoroutineManager.h"
#include"World.h"
#include<iostream>
PlayerControllerComponent::PlayerControllerComponent(Entity* entity):ControllerComponent(entity)
{
	moveStateMachine = std::make_unique<MoveStateMachine>(this);
	actionStateMachine = std::make_unique<ActionStateMachine>(this);
}
void PlayerControllerComponent::Update()
{
	PreIsGround = IsGround;
	IsGround = false;
	auto& p = rigidBody2DComponent->collideContact;
	for (auto& t : p) {
		if (t.other->GetComponent<Collider2DComponent>()->layer == PhysicsLayer::Wall && t.normal == Vec2(0, -1))IsGround = true;
	}
	IsSlide = false;
	for (auto& t : p) {
		if (t.other->GetComponent<Collider2DComponent>()->layer == PhysicsLayer::Wall && !IsGround && (t.normal == Vec2(-1, 0)||t.normal == Vec2(1, 0)))IsSlide = true;
	}
	PreSpeedX = SpeedX;
	SpeedX = rigidBody2DComponent->velocity.x;
	if (PreSpeedX == 0 && SpeedX != 0)RunStart = true;
	if (!PreIsGround && IsGround)jumpCount = 0;
	moveStateMachine->Update();
	actionStateMachine->Update();
	UpdateMoveAnimation();
	UpdateActionAnimation();
}
std::unique_ptr<Component> PlayerControllerComponent::Clone(Entity* entity)
{
	std::unique_ptr<PlayerControllerComponent>_clone = std::make_unique<PlayerControllerComponent>(entity);
	MoveStateMachine* move_machine = dynamic_cast<MoveStateMachine*>(moveStateMachine.get()->Clone(_clone.get()));
	ActionStateMachine* action_machine = dynamic_cast<ActionStateMachine*>(actionStateMachine.get()->Clone(_clone.get()));
	_clone.get()->moveStateMachine = std::move(std::unique_ptr<MoveStateMachine>(move_machine));
	_clone.get()->actionStateMachine = std::move(std::unique_ptr<ActionStateMachine>(action_machine));
	return std::move(_clone);
}
void PlayerControllerComponent::HandleJumpStart()
{
	if (!CanJump())return;
	JumpComponent* jumpComponent = owner->GetComponent<JumpComponent>();
	JumpState state = jumpComponent->jumpStates[jumpCount];
	jumpTime = 0.0f;
	if (state.needHold) {
		JumpHold = true;
	}
	else {
		rigidBody2DComponent->velocity.y -= state.Yspeed;
	}
	jumpCount++;
	if (jumpCount == 2)animationComponent->SetTrigger("JumpTwo", 0);
}

void PlayerControllerComponent::HandleJumpIng()
{
	if (!JumpHold)return;
	jumpTime += EngineTime::deltaTime();
	JumpComponent* jumpComponent = owner->GetComponent<JumpComponent>();
	JumpState state = jumpComponent->jumpStates[jumpCount - 1];
	if (jumpTime >= state.maxHoldTime) {
		animationComponent->SetTrigger("JumpStart", 0);
		rigidBody2DComponent->velocity.y -= state.Yspeed;
		JumpHold = false;
	}
}

void PlayerControllerComponent::HandleJumpEnd()
{
	if (!JumpHold)return;
	animationComponent->SetTrigger("JumpStart", 0);
	JumpComponent* jumpComponent = owner->GetComponent<JumpComponent>();
	JumpState state = jumpComponent->jumpStates[jumpCount - 1];
	rigidBody2DComponent->velocity.y -= (jumpTime / state.maxHoldTime) * state.Yspeed;
	JumpHold = false;
}

void PlayerControllerComponent::HandleRun(bool left)
{
	MoveComponent* moveComponent = owner->GetComponent<MoveComponent>();
	if (RunStart)animationComponent->SetTrigger("RunStart", 0);
	if (left)rigidBody2DComponent->velocity.x -= moveComponent->Xspeed * EngineTime::deltaTime();
	else rigidBody2DComponent->velocity.x += moveComponent->Xspeed * EngineTime::deltaTime();
}

void PlayerControllerComponent::UpdateMoveAnimation()
{
	animationComponent->SetFlip(faceLeft);
	animationComponent->SetFloat("Xspeed", std::abs(rigidBody2DComponent->velocity.x), 0);
	animationComponent->SetFloat("Yspeed", rigidBody2DComponent->velocity.y, 0);
	animationComponent->SetFloat("JumpCount", jumpCount, 0);
	animationComponent->SetBool("IsGround", IsGround, 0);
	animationComponent->SetBool("IsSlide", IsSlide, 0);
}

void PlayerControllerComponent::UpdateActionAnimation()
{
	animationComponent->SetBool("Face", faceLeft, 1);
}

void PlayerControllerComponent::SetStateStart(StateType stateType, const std::string& name)
{
	if (stateType == StateType::MoveState)
		moveStateMachine->SetStartState(name);
	else actionStateMachine->SetStartState(name);
}

void PlayerControllerComponent::AddState(StateType stateType, const std::string& name, std::unique_ptr<BaseState> state)
{
	if (stateType == StateType::MoveState)
		moveStateMachine->AddState(name, std::move(state));
	else actionStateMachine->AddState(name, std::move(state));
}

void PlayerControllerComponent::HandleSlideStart()
{
	rigidBody2DComponent->gravityScale = 2.0f;
	jumpCount = 0;
	rigidBody2DComponent->velocity.y = 0.0f;
}

void PlayerControllerComponent::HandleSlideEnd()
{
	rigidBody2DComponent->gravityScale = 50.0f;
}

void PlayerControllerComponent::HandleSlideJump()
{
	if (faceLeft)rigidBody2DComponent->velocity.x += 50.0f;
	else rigidBody2DComponent->velocity.x -= 50.0f;
	rigidBody2DComponent->velocity.y -= 150.0f;
	animationComponent->SetTrigger("SlideJump", 0);
	jumpCount++;
}

void PlayerControllerComponent::HandleAttackForward()
{
	TransformComponent* transformComponent = owner->GetComponent<TransformComponent>();
	animationComponent->SetTrigger("AttackForward", 1);
	Entity*entity = World::Instance()->Instantiate("PItem_Attack_Forward",this->owner);
	AnimationComponent*attack_Animation = entity->GetComponent<AnimationComponent>();
	attack_Animation->SetStartState("P_Attack_Forward", 0);
	attack_Animation->SetFlip(faceLeft);
	TransformComponent* attack_Transform = entity->GetComponent<TransformComponent>();
	float x = (faceLeft ? -1 : 1) * 50;
	attack_Transform->pos = Vec2(x, 0);
}

void PlayerControllerComponent::HandleAttackUp()
{
	animationComponent->SetTrigger("AttackUp", 1);
	TransformComponent* transformComponent = owner->GetComponent<TransformComponent>();
	animationComponent->SetTrigger("AttackUp", 1);
	Entity* entity = World::Instance()->Instantiate("PItem_Attack_Up", this->owner);
	AnimationComponent* attack_Animation = entity->GetComponent<AnimationComponent>();
	attack_Animation->SetStartState("P_Attack_Up", 0);
	attack_Animation->SetFlip(faceLeft);
	TransformComponent* attack_Transform = entity->GetComponent<TransformComponent>();
	attack_Transform->pos = Vec2(0, -50);
}

void PlayerControllerComponent::HandleAttackDown()
{
	animationComponent->SetTrigger("AttackDown", 1);
	TransformComponent* transformComponent = owner->GetComponent<TransformComponent>();
	animationComponent->SetTrigger("AttackDown", 1);
	Entity* entity = World::Instance()->Instantiate("PItem_Attack_Down", this->owner);
	AnimationComponent* attack_Animation = entity->GetComponent<AnimationComponent>();
	attack_Animation->SetStartState("P_Attack_Down", 0);
	attack_Animation->SetFlip(faceLeft);
	TransformComponent* attack_Transform = entity->GetComponent<TransformComponent>();
	attack_Transform->pos = Vec2(0, 50);
}

void PlayerControllerComponent::HandleHurtStart()
{
	IsHurt = false;
	animationComponent->SetTrigger("Hurt", 1);
	animationComponent->SetBool("HurtState", true, 1);
	std::vector<CoroutineStep>timeline;
	Move_Num++;
	Jump_Num++;
	
	timeline.push_back({ 0.0f,1.0f,
		[](Entity* entity) {
			bool faceLeft = entity->GetComponent<PlayerControllerComponent>()->faceLeft;
			entity->GetComponent<RigidBody2DComponent>()->velocity.x = faceLeft ? 200.0f : -200.0f;
		},nullptr,
		[](Entity* entity) {
			bool faceLeft = entity->GetComponent<PlayerControllerComponent>()->faceLeft;
			entity->GetComponent<RigidBody2DComponent>()->velocity.x = 0;
		} });
		CoroutineManager::Instance()->StartCoroutine(this->GetOwner(), "Hurt", timeline);
}

void PlayerControllerComponent::HandleHurtEnd()
{
	Move_Num--;
	Jump_Num--;
	animationComponent->SetBool("HurtState", false, 1);
	std::cout << "Player�뿪Hurt״̬" << std::endl;
}


void PlayerControllerComponent::SetAnimationActive(bool active, int layer)
{
	animationComponent->SetActive(active, layer);
}

bool PlayerControllerComponent::CanMove()
{
	return Move_Num == 0;
}

bool PlayerControllerComponent::CanJump()
{
	JumpComponent* jumpComponent = owner->GetComponent<JumpComponent>();
	return Jump_Num == 0 && jumpCount < jumpComponent->jumpCount;
}

bool PlayerControllerComponent::GetActive(int layer)
{
	return animationComponent->GetActive(layer);
}
