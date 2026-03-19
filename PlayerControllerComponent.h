#pragma once
#include"ControllerComponent.h"
#include<string>
#include<memory>
enum StateType {
	MoveState,
	ActionState
};
class BaseState;
class MoveStateMachine;
class ActionStateMachine;
class PlayerControllerComponent :public ControllerComponent {
public:
	PlayerControllerComponent(Entity* entity);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	int jumpCount = 0;
	float jumpTime = 0.0f;
	bool JumpHold = false;//跳跃蓄力


	bool faceLeft = false;

	//锁变量
	int Move_Num = 0;
	int Jump_Num = 0;

	//物理量
	bool IsGround = false;
	bool PreIsGround = false;
	bool RunStart = false;
	bool IsSlide = false;
	float SpeedX = 0.0f;
	float PreSpeedX = 0.0f;
	//hurt状态量
	bool IsHurt = false;

	void HandleJumpStart();
	void HandleJumpIng();
	void HandleJumpEnd();
	void HandleRun(bool left);
	void UpdateMoveAnimation();
	void UpdateActionAnimation();
	void SetStateStart(StateType stateType,const std::string& name);
	void AddState(StateType stateType, const std::string& name, std::unique_ptr<BaseState> state);
	void HandleSlideStart();
	void HandleSlideEnd();
	void HandleSlideJump();
	void HandleAttackForward();
	void HandleAttackUp();
	void HandleAttackDown();
	void HandleHurtStart();
	void HandleHurtEnd();

	void SetAnimationActive(bool active, int layer);
	bool CanMove();
	bool CanJump();

	bool GetActive(int layer);
	std::unique_ptr<MoveStateMachine>moveStateMachine;
	std::unique_ptr<ActionStateMachine>actionStateMachine;
private:
};