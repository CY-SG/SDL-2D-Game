#include "AIControllerComponent.h"
#include "RigidBody2DComponent.h"
#include"Collider2DComponent.h"
#include"Entity.h"
#include"AIStateMachine.h"
#include"StateMachine.h"
#include"AIDecisionMachine.h"
#include"TagComponent.h"
#include<iostream>
#include"AnimationComponent.h"
#include"EngineTime.h"
void AIControllerComponent::Update()
{
    IsGround = false;
    auto& p = rigidBody2DComponent->collideContact;
    for (auto& t : p) {
        if (t.other->GetComponent<Collider2DComponent>()->layer == PhysicsLayer::Wall && t.normal == Vec2(0, -1))IsGround = true;
    }
    UpdateDecision();
    aiDecStateMachine.get()->Update();
    aiStateMachine.get()->Update();
    UpdateAnimation();
}

AIControllerComponent::AIControllerComponent(Entity* entity):ControllerComponent(entity)
{
    aiStateMachine = std::make_unique<AIStateMachine>(this);
    aiDecStateMachine = std::make_unique<AIDecisionMachine>(this);
    IsGround = false;
    HandleAttack = nullptr;
    HandleJump = nullptr;
    HandleRun = nullptr;
    faceleft = true;
    IsHurt = false;
}

std::unique_ptr<Component> AIControllerComponent::Clone(Entity* entity)
{
    std::unique_ptr<AIControllerComponent>_clone = std::make_unique<AIControllerComponent>(entity);
    AIStateMachine* _cloneState = dynamic_cast<AIStateMachine*>(aiStateMachine.get()->Clone(_clone.get()));
    AIDecisionMachine* _cloneDec = dynamic_cast<AIDecisionMachine*>(aiDecStateMachine.get()->Clone(_clone.get()));
    _clone.get()->aiStateMachine = std::move(std::unique_ptr<AIStateMachine>(_cloneState));
    _clone.get()->aiDecStateMachine = std::move(std::unique_ptr<AIDecisionMachine>(_cloneDec));
    _clone.get()->HandleAttack = this->HandleAttack;
    _clone.get()->HandleJump = this->HandleJump;
    _clone.get()->HandleRun = this->HandleRun;
    _clone.get()->HandleIdle = this->HandleIdle;
    return std::move(_clone);
}

void AIControllerComponent::SetStateStart(AIStateType type, const std::string& name)
{
    if (type == AIStateType::Action)aiStateMachine.get()->SetStartState(name);
    else aiDecStateMachine.get()->SetStartState(name);
}

void AIControllerComponent::FlipDir()
{
    faceleft = !faceleft;
}

bool AIControllerComponent::CanMove()
{
    return true;
}

bool AIControllerComponent::CanJump()
{
    return true;
}

bool AIControllerComponent::CanAttack()
{
    return true;
}

void AIControllerComponent::HandleHurtStart()
{
    animationComponent->SetTrigger("Hurt", 0);
}

void AIControllerComponent::HandleAttackStart()
{
    animationComponent->SetTrigger("Attack", 0);
}

void AIControllerComponent::UpdateDecision()
{
    auto& bb = blackBoard;

    // reset
    bb.playerVisible = false;
    bb.wallAhead = false;
    if (groundInitialized)
        bb.groundAhead = !footSensor.empty();
    else
        bb.groundAhead = true;

    if (!footSensor.empty())
        groundInitialized = true;
    bb.target = nullptr;
    bb.upperWall = this->upperWall;
    bb.lowerWall = this->lowerWall;
    bb.playerInAttackRange = this->playerInAttackRange;


    // 处理 vision sensor
    for (auto& t : visionSensor)
    {
        Entity* entity = t.entity;
        Vec2 dis = t.dis;

        TagComponent* tag = entity->GetComponent<TagComponent>();

        if (tag->tag == Tag::WallTag && std::abs(dis.x) <= 40.0f)
        {
            bb.wallAhead = true;
        }

        if (tag->tag == Tag::PlayerTag)
        {
            bb.playerVisible = true;
            bb.target = entity;
        }
    }

    // 记忆系统
    if (bb.playerVisible)
    {
        bb.loseSightTimer = 0.0f;
    }
    else
    {
        bb.loseSightTimer += EngineTime::deltaTime();
    }

    // 清空 sensor
    visionSensor.clear();
    footSensor.clear();
    playerInAttackRange = false;
    lowerWall = false;
    upperWall = false;
}

void AIControllerComponent::UpdateAnimation()
{
    animationComponent->SetFlip(!faceleft);
    animationComponent->SetFloat("Xspeed", std::abs(rigidBody2DComponent->velocity.x), 0);
    animationComponent->SetFloat("Yspeed", rigidBody2DComponent->velocity.y, 0);
    animationComponent->SetBool("IsGround", IsGround, 0);
    animationComponent->SetBool("HurtState", IsHurt, 0);
}
