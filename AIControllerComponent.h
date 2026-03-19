#pragma once
#include"ControllerComponent.h"
#include"AIDecisionMachine.h"
#include<functional>
#include<memory>
enum AIMoveMode {
	AIMoveNormal,
	AIMoveChase
};
enum AttackMode {
	AIAttackNormal
};
enum AIStateType {
	Action,
	Decision
};
struct PerceivedEntity {
	Entity* entity;
	Vec2 dis;
};
struct AIBlackboard
{
	bool playerVisible = false;
	bool wallAhead = false;
	bool groundAhead = true;
	bool playerInAttackRange = false;
	bool lowerWall = false;
	bool upperWall = false;
	Entity* target = nullptr;

	float loseSightTimer = 0.0f;

};
class AIStateMachine;
class AIControllerComponent :public ControllerComponent {
public:
	void Update()override;
	AIControllerComponent(Entity* entity);
	std::unique_ptr<Component>Clone(Entity* entity);
	std::function<void(Entity* ,bool faceLeft)>HandleRun;
	std::function<void(Entity*, bool faceLeft)>HandleJump;
	std::function<void(Entity*, bool faceLeft)>HandleAttack;
	std::function<void(Entity*, bool faceLeft)>HandleIdle;
	std::function<void(Entity*, bool faceLeft)>HandleHurt;
	std::unique_ptr<AIStateMachine>aiStateMachine;
	std::unique_ptr<AIDecisionMachine>aiDecStateMachine;
	void SetStateStart(AIStateType type, const std::string& name);
	void FlipDir();
	bool CanMove();
	bool CanJump();
	bool CanAttack();
	void HandleHurtStart();
	void HandleAttackStart();

	bool IsGround;
	bool faceleft;
	bool IsHurt;
	//行为模式
	AIMoveMode aiMoveMode;
	AttackMode aiAttackMode;

	//AI决策
	AIBlackboard blackBoard;
	float visibleMemoryTime = 2.0f;
	float patrolTime = 2.0f;
	float attackCooldown = 1.0f;
	float hurtCoolddown = 0.5f;
	float jumpCooldown = 3.0f;
	bool groundInitialized = false;
	//Sensor缓存
	std::vector<PerceivedEntity>visionSensor;
	std::vector<PerceivedEntity>footSensor;
	bool playerInAttackRange = false;
	bool lowerWall = false;
	bool upperWall = false;

	//Controller更新决策状态
	void UpdateDecision();
private:
	void UpdateAnimation();
};