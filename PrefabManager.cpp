#include "PrefabManager.h"
#include"AnimationClipManager.h"
#include"SDLResourceManager.h"
#include"AnimationComponent.h"
#include"RigidBody2DComponent.h"
#include"InputComponent.h"
#include"Collider2DComponent.h"
#include"TransformComponent.h"
#include"MoveComponent.h"
#include"JumpComponent.h"
#include"DamageComponent.h"
#include"HpComponent.h"
#include"TagComponent.h"
#include"LifeTimeComponent.h"
#include"AnimationState.h"
#include"PlayerControllerComponent.h"
#include"AIControllerComponent.h"
#include"AISensorController.h"
#include"StateMachine.h"
#include"PSlideState.h"
#include"MoveStateMachine.h"
#include"ActionStateMachine.h"
#include"PNoneState.h"
#include"PAttackForwardState.h"
#include"AIInput.h"
#include"AIStateMachine.h"
#include"PNormalState.h"
#include"PAttackDownState.h"
#include"PAttackUpState.h"
#include"PHurtState.h"
#include<memory>
#include"SDLInput.h"
#include"Entity.h"
#include"CoroutineManager.h"
#include<iostream>
#include"World.h"
#include"CameraSystem.h"
#include"Camera2D.h"
std::unique_ptr<Entity> PrefabManager::GetPrefab(const std::string& name)
{
	return std::move(PrefabMap[name].get()->Clone());
}

void PrefabManager::Initial(ResourceManager* resourceManager, AnimationClipManager* animationClipManager)
{
	this->animationClipManager = animationClipManager;
	this->resourceManager = resourceManager;
	LoadSensor();
	LoadWall();
	LoadPlayerPrefab();
	LoadItems();
}

PrefabManager::PrefabManager()
{

}

void PrefabManager::LoadPlayerPrefab()
{
	//加载Texture
//
//加载Player-Idle
	std::vector<std::shared_ptr<Texture>>P_Idle_Texture(9);
	const std::string P_Idle_Texture_Path = "Sprites/Player/Idle/";
	for (int i = 0; i < 9; i++) {
		const std::string path = P_Idle_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_Idle_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-JumpDown
	std::vector<std::shared_ptr<Texture>>P_JumpDown_Texture(3);
	const std::string P_JumpDown_Texture_Path = "Sprites/Player/Jump/Repeat/";
	for (int i = 0; i < 3; i++) {
		const std::string path = P_JumpDown_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_JumpDown_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-JumpUp
	std::vector<std::shared_ptr<Texture>>P_JumpUp_Texture(9);
	const std::string P_JumpUp_Texture_Path = "Sprites/Player/Jump/Up/";
	for (int i = 0; i < 9; i++) {
		const std::string path = P_JumpUp_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_JumpUp_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-RunStart
	std::vector<std::shared_ptr<Texture>>P_RunStart_Texture(3);
	const std::string P_Run_Texture_Path = "Sprites/Player/Run/";
	for (int i = 0; i < 3; i++) {
		const std::string path = P_Run_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_RunStart_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-RunLoop
	std::vector<std::shared_ptr<Texture>>P_RunLoop_Texture(5);
	for (int i = 3; i < 8; i++) {
		const std::string path = P_Run_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_RunLoop_Texture[i - 3] = resourceManager->LoadTexture(path);
	}
	//加载Player-TwoJump
	std::vector<std::shared_ptr<Texture>>P_TwoJump_Texture(4);
	const std::string P_TwoJump_Texture_Path = "Sprites/Player/Jump/JumpTwo/";
	for (int i = 0; i < 4; i++) {
		const std::string path = P_TwoJump_Texture_Path + "0" + std::to_string(i + 1) + ".PNG";
		P_TwoJump_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-Slide
	std::vector<std::shared_ptr<Texture>>P_Slide_Texture(3);
	const std::string P_Slide_Texture_Path = "Sprites/Player/Climb/Climb/";
	for (int i = 0; i < 3; i++) {
		const std::string path = P_Slide_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_Slide_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-SlideJump
	std::vector<std::shared_ptr<Texture>>P_SlideJump_Texture(3);
	const std::string P_SlideJump_Texture_Path = "Sprites/Player/Climb/ClimbJump/";
	for (int i = 0; i < 3; i++) {
		const std::string path = P_SlideJump_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_SlideJump_Texture[i] = resourceManager->LoadTexture(path);
	}

	//加载Player-AttackLeft
	std::vector<std::shared_ptr<Texture>>P_AttackLeft_Texture(5);
	const std::string P_AttackLeft_Texture_Path = "Sprites/Player/Attack/AttackLeft/";
	for (int i = 0; i < 5; i++) {
		const std::string path = P_AttackLeft_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_AttackLeft_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-AttackRight
	std::vector<std::shared_ptr<Texture>>P_AttackRight_Texture(5);
	const std::string P_AttackRight_Texture_Path = "Sprites/Player/Attack/AttackRight/";
	for (int i = 0; i < 5; i++) {
		const std::string path = P_AttackRight_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_AttackRight_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-AttackUp
	std::vector<std::shared_ptr<Texture>>P_AttackUp_Texture(5);
	const std::string P_AttackUp_Texture_Path = "Sprites/Player/Attack/AttackUp/";
	for (int i = 0; i < 5; i++) {
		const std::string path = P_AttackUp_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_AttackUp_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-AttackDown
	std::vector<std::shared_ptr<Texture>>P_AttackDown_Texture(5);
	const std::string P_AttackDown_Texture_Path = "Sprites/Player/Attack/AttackDown/";
	for (int i = 0; i < 5; i++) {
		const std::string path = P_AttackDown_Texture_Path + std::to_string(i + 1) + ".PNG";
		P_AttackDown_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载Player-Hurt
	std::vector<std::shared_ptr<Texture>>P_Hurt_Texture(4);
	const std::string P_Hurt_Texture_Path = "Sprites/Player/Hit/Hit";
	for (int i = 0; i < 4; i++) {
		const std::string path = P_Hurt_Texture_Path + std::to_string(i + 1) + ".png";
		P_Hurt_Texture[i] = resourceManager->LoadTexture(path);
	}
	//加载animation
	//
	//Move资源
	//加载Player-Idle
	std::shared_ptr<AnimationClip>P_Idle_Animation = animationClipManager->LoadAnimationClip("P_Idle", P_Idle_Texture, 0.1f, true);
	//加载Player-JumpDown
	std::shared_ptr<AnimationClip>P_JumpDown_Animation = animationClipManager->LoadAnimationClip("P_JumpDown", P_JumpDown_Texture, 0.1f, true);
	//加载Player-JumpUp
	std::shared_ptr<AnimationClip>P_JumpUp_Animation = animationClipManager->LoadAnimationClip("P_JumpUp", P_JumpUp_Texture, 0.2f, false);
	//加载Player-RunStart
	std::shared_ptr<AnimationClip>P_RunStart_Animation = animationClipManager->LoadAnimationClip("P_RunStart", P_RunStart_Texture, 0.1f, false);
	//加载Player-RunLoop
	std::shared_ptr<AnimationClip>P_RunLoop_Animation = animationClipManager->LoadAnimationClip("P_RunLoop", P_RunLoop_Texture, 0.3f, true);
	//加载Player-TwoJump
	std::shared_ptr<AnimationClip>P_TwoJump_Animation = animationClipManager->LoadAnimationClip("P_TwoJump", P_TwoJump_Texture, 0.1f, false);
	//加载Player-Slide
	std::shared_ptr<AnimationClip>P_Slide_Animation = animationClipManager->LoadAnimationClip("P_Slide", P_Slide_Texture, 0.1f, true);
	//加载Player-SlideJump
	std::shared_ptr<AnimationClip>P_SlideJump_Animation = animationClipManager->LoadAnimationClip("P_SlideJump", P_SlideJump_Texture, 0.15f, false);
	//Action资源
	//加载Player-AttackLeft
	std::shared_ptr<AnimationClip>P_AttackLeft_Animation = animationClipManager->LoadAnimationClip("P_AttackLeft", P_AttackLeft_Texture, 0.15f, false);
	//加载Player-AttackRight
	std::shared_ptr<AnimationClip>P_AttackRight_Animation = animationClipManager->LoadAnimationClip("P_AttackRight", P_AttackRight_Texture, 0.15f, false);
	//加载Player-AttackUp
	std::shared_ptr<AnimationClip>P_AttackUp_Animation = animationClipManager->LoadAnimationClip("P_AttackUp", P_AttackUp_Texture, 0.15f, false);
	//加载Player-AttackDown
	std::shared_ptr<AnimationClip>P_AttackDown_Animation = animationClipManager->LoadAnimationClip("P_AttackDown", P_AttackDown_Texture, 0.15f, false);
	//加载Player-Hurt
	std::shared_ptr<AnimationClip>P_Hurt_Animation = animationClipManager->LoadAnimationClip("P_Hurt", P_Hurt_Texture, 0.2f, false);
	//加载Player相关组件

	Entity* player = new Entity("Player");
	PrefabMap["Player"] = std::move(std::unique_ptr<Entity>(player));
	SDLInput* P_Input = new SDLInput();
	std::vector<JumpState>P_Jump = { {150.0f,0.5f,true},{200.0f,0.0f,false} };
	//组件
	RigidBody2DComponent* P_rigidBody2DComponent = player->AddComponent<RigidBody2DComponent>(player);
	Collider2DComponent* P_collider2DComponent = player->AddComponent<Collider2DComponent>(player, Vec2(40, 50), Vec2(0, 10), PhysicsLayer::Player,PhysicsLayer::Wall | PhysicsLayer::EnemyTrigger | PhysicsLayer::Default);
	AnimationComponent* P_animationComponent = player->AddComponent<AnimationComponent>(player, 2, std::vector<float>{1.0f, 1.0f}, std::vector<bool>{true, true}, std::vector<bool>{true, false});
	InputComponent* P_inputComponent = player->AddComponent<InputComponent>(player, P_Input);
	MoveComponent* P_moveComponent = player->AddComponent<MoveComponent>(player, 150.0f);
	JumpComponent* P_jumpComponent = player->AddComponent<JumpComponent>(player, 2, P_Jump);
	TagComponent* P_tagComponent = player->AddComponent<TagComponent>(player, Tag::PlayerTag);
	HpComponent* P_hpComponent = player->AddComponent<HpComponent>(player, 100);
	PlayerControllerComponent* P_controllerComponent = player->AddComponent<PlayerControllerComponent>(player);

	//组件设置
	TransformComponent* P_transformComponent = player->GetComponent<TransformComponent>();
	P_transformComponent->pos = Vec2(100, 150);
	std::unique_ptr<PNormalState>P_NormalState_Machine = std::make_unique<PNormalState>(P_controllerComponent->moveStateMachine.get());
	std::unique_ptr<PSlideState>P_SlideState_Machine = std::make_unique<PSlideState>(P_controllerComponent->moveStateMachine.get());
	std::unique_ptr<PNoneState>P_NoneState_Machine = std::make_unique<PNoneState>(P_controllerComponent->actionStateMachine.get());
	std::unique_ptr<PAttackForwardState>P_AttackForwardState_Machine = std::make_unique<PAttackForwardState>(P_controllerComponent->actionStateMachine.get());
	std::unique_ptr<PAttackUpState>P_AttackUpState_Machine = std::make_unique<PAttackUpState>(P_controllerComponent->actionStateMachine.get());
	std::unique_ptr<PAttackDownState>P_AttackDownState_Machine = std::make_unique<PAttackDownState>(P_controllerComponent->actionStateMachine.get());
	std::unique_ptr<PHurtState>P_HurtState_Machine = std::make_unique<PHurtState>(P_controllerComponent->actionStateMachine.get());
	P_controllerComponent->AddState(StateType::MoveState, "P_Normal", std::move(P_NormalState_Machine));
	P_controllerComponent->AddState(StateType::MoveState, "P_Slide", std::move(P_SlideState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_None", std::move(P_NoneState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackForward", std::move(P_AttackForwardState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackUp", std::move(P_AttackUpState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackDown", std::move(P_AttackDownState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_Hurt", std::move(P_HurtState_Machine));
	P_controllerComponent->SetStateStart(StateType::MoveState, "P_Normal");
	P_controllerComponent->SetStateStart(StateType::ActionState, "P_None");
	P_animationComponent->SetScale(0.5f, 0);
	P_animationComponent->SetScale(0.5f, 1);
	P_rigidBody2DComponent->gravityScale = 50.0f;
	//动画设置

	//动画状态机参数
	//Move层
	P_animationComponent->AddAnimationParam("Xspeed", AnimatorParam(ParamType::Float), 0);
	P_animationComponent->AddAnimationParam("Yspeed", AnimatorParam(ParamType::Float), 0);
	P_animationComponent->AddAnimationParam("IsGround", AnimatorParam(ParamType::Bool), 0);
	P_animationComponent->AddAnimationParam("JumpStart", AnimatorParam(ParamType::Trigger), 0);
	P_animationComponent->AddAnimationParam("JumpCount", AnimatorParam(ParamType::Float), 0);
	P_animationComponent->AddAnimationParam("RunStart", AnimatorParam(ParamType::Trigger), 0);
	P_animationComponent->AddAnimationParam("JumpTwo", AnimatorParam(ParamType::Trigger), 0);
	P_animationComponent->AddAnimationParam("IsSlide", AnimatorParam(ParamType::Bool), 0);
	P_animationComponent->AddAnimationParam("SlideJump", AnimatorParam(ParamType::Trigger), 0);
	//Action层
	P_animationComponent->AddAnimationParam("FaceLeft", AnimatorParam(ParamType::Bool), 1);
	P_animationComponent->AddAnimationParam("AttackForward", AnimatorParam(ParamType::Trigger), 1);
	P_animationComponent->AddAnimationParam("AttackUp", AnimatorParam(ParamType::Trigger), 1);
	P_animationComponent->AddAnimationParam("AttackDown", AnimatorParam(ParamType::Trigger), 1);
	P_animationComponent->AddAnimationParam("Hurt", AnimatorParam(ParamType::Trigger), 1);
	P_animationComponent->AddAnimationParam("HurtState", AnimatorParam(ParamType::Bool), 0);
	//动画绑定clip
	//Move动画
	std::shared_ptr<AnimationState>P_IdleState = std::make_shared<AnimationState>("P_Idle", P_Idle_Animation);
	std::shared_ptr<AnimationState>P_RunStartState = std::make_shared<AnimationState>("P_RunStart", P_RunStart_Animation);
	std::shared_ptr<AnimationState>P_RunLoopState = std::make_shared<AnimationState>("P_RunLoop", P_RunLoop_Animation);
	std::shared_ptr<AnimationState>P_JumpDownState = std::make_shared<AnimationState>("P_JumpDown", P_JumpDown_Animation);
	std::shared_ptr<AnimationState>P_JumpUpState = std::make_shared<AnimationState>("P_JumpUp", P_JumpUp_Animation);
	std::shared_ptr<AnimationState>P_TwoJumpState = std::make_shared<AnimationState>("P_TwoJump", P_TwoJump_Animation);
	std::shared_ptr<AnimationState>P_SlideState = std::make_shared<AnimationState>("P_Slide", P_Slide_Animation);
	std::shared_ptr<AnimationState>P_SlideJumpState = std::make_shared<AnimationState>("P_SlideJump", P_SlideJump_Animation);
	//Action动画
	std::shared_ptr<AnimationState>P_AttackLeftState = std::make_shared<AnimationState>("P_AttackLeft", P_AttackLeft_Animation);
	std::shared_ptr<AnimationState>P_AttackRightState = std::make_shared<AnimationState>("P_AttackRight", P_AttackRight_Animation);
	std::shared_ptr<AnimationState>P_AttackUpState = std::make_shared<AnimationState>("P_AttackUp", P_AttackUp_Animation);
	std::shared_ptr<AnimationState>P_AttackDownState = std::make_shared<AnimationState>("P_AttackDown", P_AttackDown_Animation);
	std::shared_ptr<AnimationState>P_HurtState = std::make_shared<AnimationState>("P_Hurt", P_Hurt_Animation);
	std::shared_ptr<AnimationState>P_NoneState = std::make_shared<AnimationState>("P_None", nullptr);
	//设置动画状态机
	//Move层
	P_IdleState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_RunStart", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Greater, 0.0f),
			TransitionCondition("Yspeed", CompareOp::Less, 0.1f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f),
			TransitionCondition("RunStart", CompareOp::Trigger, 0.0f)
	}, 0.0f));
	//P_IdleState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpUp", std::vector<TransitionCondition>{
	//	TransitionCondition("JumpStart",CompareOp::Trigger,0.0f),
	//	TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
	//	TransitionCondition("IsGround", CompareOp::False, 0.0f)
	//}, 0.0f));
	P_IdleState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{
		TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
			TransitionCondition("IsGround", CompareOp::False, 0.0f)
	}, 0.0f));
	P_JumpDownState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_Idle", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Less, 0.1f),
			TransitionCondition("Yspeed", CompareOp::Same, 0.0f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f)
	}, 0.0f));
	P_JumpDownState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_RunLoop", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Greater, 0.0f),
			TransitionCondition("Yspeed", CompareOp::Same, 0.0f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f)
	}, 0.0f));
	P_JumpDownState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_TwoJump", std::vector<TransitionCondition>{
		TransitionCondition("IsGround", CompareOp::False, 0.0f),
			TransitionCondition("JumpCount", CompareOp::Same, 2.0f),
			TransitionCondition("JumpTwo", CompareOp::Trigger, 0.0f)
	}, 0.0f));
	P_JumpDownState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_Slide", std::vector<TransitionCondition>{
		TransitionCondition("IsSlide", CompareOp::True, 0.0f)
	}, 0.0f));
	//P_JumpUpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{

	//}, 2.0f));
	P_RunStartState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_Idle", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Same, 0.0f),
			TransitionCondition("Yspeed", CompareOp::Same, 0.0f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f)
	}, 0.0f));
	//P_RunStartState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpUp", std::vector<TransitionCondition>{
	//	TransitionCondition("JumpStart", CompareOp::Trigger, 0.0f),
	//	TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
	//	TransitionCondition("IsGround", CompareOp::False, 0.0f)
	//}, 0.0f));
	P_RunStartState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{
		TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
			TransitionCondition("IsGround", CompareOp::False, 0.0f)
	}, 0.0f));
	P_RunStartState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_RunLoop", std::vector<TransitionCondition>{

	}, 1.0f));
	P_RunLoopState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_Idle", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Less, 0.1f),
			TransitionCondition("Yspeed", CompareOp::Same, 0.0f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f)
	}, 0.0f));
	//P_RunLoopState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpUp", std::vector<TransitionCondition>{
	//	TransitionCondition("JumpStart", CompareOp::Trigger, 0.0f),
	//	TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
	//	TransitionCondition("IsGround", CompareOp::False, 0.0f)
	//}, 0.0f));
	P_RunLoopState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{
		TransitionCondition("Yspeed", CompareOp::NotSame, 0.0f),
			TransitionCondition("IsGround", CompareOp::False, 0.0f)
	}, 0.0f));
	P_TwoJumpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{

	}, 1.0f));
	P_TwoJumpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_Slide", std::vector<TransitionCondition>{
		TransitionCondition("IsSlide", CompareOp::True, 0.0f)
	}, 0.0f));
	P_SlideState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{
		TransitionCondition("IsSlide", CompareOp::False, 0.0f)
	}, 0.0f));
	P_SlideState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_SlideJump", std::vector<TransitionCondition>{
		TransitionCondition("SlideJump", CompareOp::Trigger, 0.0f)
	}, 0.0f));
	P_SlideJumpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_JumpDown", std::vector<TransitionCondition>{

	}, 0.6f));
	P_SlideJumpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_TwoJump", std::vector<TransitionCondition>{
		TransitionCondition("IsGround", CompareOp::False, 0.0f),
			TransitionCondition("JumpCount", CompareOp::Same, 2.0f),
			TransitionCondition("JumpTwo", CompareOp::Trigger, 0.0f)
	}, 0.0f));
	//Action层
	P_AttackLeftState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_None", std::vector<TransitionCondition>{

	}, 0.7f));
	P_AttackRightState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_None", std::vector<TransitionCondition>{

	}, 0.7f));
	P_AttackDownState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_None", std::vector<TransitionCondition>{

	}, 0.7f));
	P_AttackUpState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_None", std::vector<TransitionCondition>{

	}, 0.7f));
	P_HurtState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_None", std::vector<TransitionCondition>{

	}, 1.0f));
	//Any->Attack-Left
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackLeft", std::vector<TransitionCondition>{
		TransitionCondition("FaceLeft", CompareOp::True, 0.0f),
			TransitionCondition("AttackForward", CompareOp::Trigger, 0.0f),
			TransitionCondition("HurtState", CompareOp::False, 0.0f)
	}, 0.0f), 1);
	//Any->Attack-Right
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackRight", std::vector<TransitionCondition>{
		TransitionCondition("FaceLeft", CompareOp::False, 0.0f),
			TransitionCondition("AttackForward", CompareOp::Trigger, 0.0f),
			TransitionCondition("HurtState", CompareOp::False, 0.0f)
	}, 0.0f), 1);
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackUp", std::vector<TransitionCondition>{
		TransitionCondition("AttackUp", CompareOp::Trigger, 0.0f),
			TransitionCondition("HurtState", CompareOp::False, 0.0f)
	}, 0.0f), 1);
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackDown", std::vector<TransitionCondition>{
		TransitionCondition("AttackDown", CompareOp::Trigger, 0.0f),
			TransitionCondition("HurtState", CompareOp::False, 0.0f)
	}, 0.0f), 1);
	//Any-Hurt
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_Hurt", std::vector<TransitionCondition>{
		TransitionCondition("Hurt", CompareOp::Trigger, 0.0f),
	}, 0.0f), 1);
	//加入状态机
	//Move层
	P_animationComponent->AddAnimationState("P_Idle", P_IdleState, 0);
	P_animationComponent->AddAnimationState("P_RunStart", P_RunStartState, 0);
	P_animationComponent->AddAnimationState("P_RunLoop", P_RunLoopState, 0);
	P_animationComponent->AddAnimationState("P_JumpDown", P_JumpDownState, 0);
	P_animationComponent->AddAnimationState("P_JumpUp", P_JumpDownState, 0);
	P_animationComponent->AddAnimationState("P_TwoJump", P_TwoJumpState, 0);
	P_animationComponent->AddAnimationState("P_Slide", P_SlideState, 0);
	P_animationComponent->AddAnimationState("P_SlideJump", P_SlideJumpState, 0);
	//Action层
	P_animationComponent->AddAnimationState("P_None", P_NoneState, 1);
	P_animationComponent->AddAnimationState("P_AttackLeft", P_AttackLeftState, 1);
	P_animationComponent->AddAnimationState("P_AttackRight", P_AttackRightState, 1);
	P_animationComponent->AddAnimationState("P_AttackUp", P_AttackUpState, 1);
	P_animationComponent->AddAnimationState("P_AttackDown", P_AttackDownState, 1);
	P_animationComponent->AddAnimationState("P_Hurt", P_HurtState, 1);

	P_animationComponent->SetStartState("P_Idle", 0);
	P_animationComponent->SetStartState("P_None", 1);

}

void PrefabManager::LoadWall()
{
	//下面墙体
	Entity* Wall_1 = new Entity("Wall_1");
	PrefabMap["Wall_1"] = std::move(std::unique_ptr<Entity>(Wall_1));
	//物理组件
	Collider2DComponent* Wall_1_collider2DComponent = Wall_1->AddComponent<Collider2DComponent>(Wall_1, Vec2(800, 10), Vec2(0, 0), PhysicsLayer::Wall,PhysicsLayer::Default|PhysicsLayer::Enemy|PhysicsLayer::Player);
	TagComponent* Wall_1_tagComponent = Wall_1->AddComponent<TagComponent>(Wall_1, Tag::WallTag);
	TransformComponent* Wall_1_transformComponent = Wall_1->GetComponent<TransformComponent>();
	Wall_1_transformComponent->pos = Vec2(120, 300);

	//左边墙体
	Entity* Wall_2 = new Entity("Wall_2");
	PrefabMap["Wall_2"] = std::move(std::unique_ptr<Entity>(Wall_2));
	//物理组件
	Collider2DComponent* Wall_2_collider2DComponent = Wall_2->AddComponent<Collider2DComponent>(Wall_2, Vec2(10, 300), Vec2(0, 0), PhysicsLayer::Wall,PhysicsLayer::Default | PhysicsLayer::Enemy | PhysicsLayer::Player);
	TagComponent* Wall_2_tagComponent = Wall_2->AddComponent<TagComponent>(Wall_2, Tag::WallTag);
	TransformComponent* Wall_2_transformComponent = Wall_2->GetComponent<TransformComponent>();
	Wall_2_transformComponent->pos = Vec2(-80, 150);


	//传送门墙体
	Entity* Wall_3 = new Entity("Wall_3");
	PrefabMap["Wall_3"] = std::move(std::unique_ptr<Entity>(Wall_3));
	//物理组件
	Collider2DComponent* Wall_3_collider2DComponent = Wall_3->AddComponent<Collider2DComponent>(Wall_3, Vec2(1000, 10), Vec2(0, 0), PhysicsLayer::Wall, PhysicsLayer::Default | PhysicsLayer::Enemy | PhysicsLayer::Player);
	TagComponent* Wall_3_tagComponent = Wall_3->AddComponent<TagComponent>(Wall_3, Tag::WallTag);
	TransformComponent* Wall_3_transformComponent = Wall_3->GetComponent<TransformComponent>();
	Wall_3_transformComponent->pos = Vec2(4800.0f, 5600.0f);



	std::function<void(Entity* entityA,bool faceLeft)>Enemy_HandleRun = [](Entity* entityA, bool faceLeft)->void {
		MoveComponent* moveComponent = entityA->GetComponent<MoveComponent>();
		RigidBody2DComponent* rigidBody2DComponent = entityA->GetComponent<RigidBody2DComponent>();
		AIControllerComponent* aiControllerComponent = entityA->GetComponent<AIControllerComponent>();
		switch (aiControllerComponent->aiMoveMode)
		{
		case AIMoveMode::AIMoveNormal:rigidBody2DComponent->velocity.x = moveComponent->Xspeed * (faceLeft ? -1 : 1);
			break;
		case AIMoveMode::AIMoveChase:std::vector<CoroutineStep>timeline;
			timeline.push_back({ 0.0f,0.3f,
				nullptr,
				[](Entity* e,float t) {
					MoveComponent* moveComponent = e->GetComponent<MoveComponent>();
					bool faceLeft = e->GetComponent<AIControllerComponent>()->faceleft;
					e->GetComponent<RigidBody2DComponent>()->velocity.x = moveComponent->Xspeed * (faceLeft ? -0.4 : 0.4);
				}, nullptr });
			timeline.push_back({ 0.3f,0.5f,
				nullptr,
				[](Entity* e,float t) {
					MoveComponent* moveComponent = e->GetComponent<MoveComponent>();
					bool faceLeft = e->GetComponent<AIControllerComponent>()->faceleft;
					e->GetComponent<RigidBody2DComponent>()->velocity.x = moveComponent->Xspeed * (faceLeft ? -1.5 : 1.5);
				}, nullptr });
			CoroutineManager::Instance()->StartCoroutine(entityA, "Chase", timeline);
			break;
		}
	};

	std::function<void(Entity* entityA, bool faceLeft)>Enemy_HandleIdle = [](Entity* entityA, bool faceLeft)->void {
		MoveComponent* moveComponent = entityA->GetComponent<MoveComponent>();
		RigidBody2DComponent* rigidBody2DComponent = entityA->GetComponent<RigidBody2DComponent>();
		rigidBody2DComponent->velocity.x = 0.0f;
	};

	std::function<void(Entity* entityA, bool faceLeft)>Enemy_HandleAttack = [](Entity* entityA, bool faceLeft)->void {
		std::vector<CoroutineStep>timeline;
		timeline.push_back({ 0.0f,0.5f,nullptr,nullptr,nullptr});
		timeline.push_back({ 0.4f,0.5f,[](Entity* entity) {
		Entity* entity1 = World::Instance()->Instantiate("EItem_Attack_Forward", entity);
		TransformComponent* transformComponent = entity1->GetComponent<TransformComponent>();
		AIControllerComponent* aiControllerComponent = entity->GetComponent<AIControllerComponent>();
		bool faceLeft = aiControllerComponent->faceleft;
		transformComponent->pos.y = 30.0f;
		transformComponent->pos.x = faceLeft ? -40.0f : 40.0f;
		} ,nullptr,nullptr});

		CoroutineManager::Instance()->StartCoroutine(entityA, "Attack", timeline);
	};

	//Test敌人

	//加载敌人Texture
	//加载敌人Idle
	std::shared_ptr<Texture>E1_Idle_Texture;
	const std::string E1_Idle_Texture_Path = "Sprites/Enemy/IDLE.png";
	E1_Idle_Texture = resourceManager->LoadTexture(E1_Idle_Texture_Path);
	//加载敌人Attack
	std::shared_ptr<Texture>E1_Attack_Texture;
	const std::string E1_Attack_Texture_Path = "Sprites/Enemy/ATTACK.png";
	E1_Attack_Texture = resourceManager->LoadTexture(E1_Attack_Texture_Path);
	//加载敌人Run
	std::shared_ptr<Texture>E1_Run_Texture;
	const std::string E1_Run_Texture_Path = "Sprites/Enemy/RUN.png";
	E1_Run_Texture = resourceManager->LoadTexture(E1_Run_Texture_Path);
	//加载敌人Hurt
	std::shared_ptr<Texture>E1_Hurt_Texture;
	const std::string E1_Hurt_Texture_Path = "Sprites/Enemy/HURT.png";
	E1_Hurt_Texture = resourceManager->LoadTexture(E1_Hurt_Texture_Path);

	//加载AnimationClip
	std::shared_ptr<AnimationClip>E1_Idle_Animation = animationClipManager->LoadAnimationClip("E1_Idle", E1_Idle_Texture,10,10,1, 0.1f, true);
	std::shared_ptr<AnimationClip>E1_Attack_Animation = animationClipManager->LoadAnimationClip("E1_Attack", E1_Attack_Texture, 7, 7, 1, 0.1f, false);
	std::shared_ptr<AnimationClip>E1_Run_Animation = animationClipManager->LoadAnimationClip("E1_Run", E1_Run_Texture, 16, 16, 1, 0.05f, true);
	std::shared_ptr<AnimationClip>E1_Hurt_Animation = animationClipManager->LoadAnimationClip("E1_Hurt", E1_Hurt_Texture, 4, 4, 1, 0.15f, false);

	//动画绑定clip
	std::shared_ptr<AnimationState>E1_IdleState = std::make_shared<AnimationState>("E1_Idle", E1_Idle_Animation);
	std::shared_ptr<AnimationState>E1_RunState = std::make_shared<AnimationState>("E1_Run", E1_Run_Animation);
	std::shared_ptr<AnimationState>E1_HurtState = std::make_shared<AnimationState>("E1_Hurt", E1_Hurt_Animation);
	std::shared_ptr<AnimationState>E1_AttackState = std::make_shared<AnimationState>("E1_Attack", E1_Attack_Animation);

	Entity* Enemy_1 = new Entity("Enemy_1");
	PrefabMap["Enemy_1"] = std::move(std::unique_ptr<Entity>(Enemy_1));
	AIInput* aiInput = new AIInput();
	//物理组件
	Collider2DComponent* Enemy_1_collider2DComponent = Enemy_1->AddComponent<Collider2DComponent>(Enemy_1, Vec2(30, 50), Vec2(0, 20), PhysicsLayer::Enemy,PhysicsLayer::Wall | PhysicsLayer::Default);
	TransformComponent* Enemy_1_transformComponent = Enemy_1->GetComponent<TransformComponent>();
	AnimationComponent* Enemy_1_animationComponent = Enemy_1->AddComponent<AnimationComponent>(Enemy_1, 1, std::vector<float>{1.0f}, std::vector<bool>{true}, std::vector<bool>{true});
	RigidBody2DComponent* Enemy_1_rigidBody2DComponent = Enemy_1->AddComponent<RigidBody2DComponent>(Enemy_1);
	InputComponent* Enemy_1_inputComponent = Enemy_1->AddComponent<InputComponent>(Enemy_1,aiInput);
	AIControllerComponent* Enemy_1_aiControllerComponent = Enemy_1->AddComponent<AIControllerComponent>(Enemy_1);
	HpComponent* Enemy_1_hpComponent = Enemy_1->AddComponent<HpComponent>(Enemy_1,10);
	MoveComponent* Enemy_1_moveComponent = Enemy_1->AddComponent<MoveComponent>(Enemy_1, 150.0f);
	TagComponent* Enemy_1_tagComponent = Enemy_1->AddComponent<TagComponent>(Enemy_1, Tag::EnemyTag);
	
	//设置动画参数
	Enemy_1_animationComponent->AddAnimationParam("Xspeed", AnimatorParam(ParamType::Float), 0);
	Enemy_1_animationComponent->AddAnimationParam("Yspeed", AnimatorParam(ParamType::Float), 0);
	Enemy_1_animationComponent->AddAnimationParam("Attack", AnimatorParam(ParamType::Trigger), 0);
	Enemy_1_animationComponent->AddAnimationParam("Hurt", AnimatorParam(ParamType::Trigger), 0);
	Enemy_1_animationComponent->AddAnimationParam("HurtState", AnimatorParam(ParamType::Bool), 0);
	Enemy_1_animationComponent->AddAnimationParam("IsGround", AnimatorParam(ParamType::Bool), 0);
	
	E1_IdleState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("E1_Run", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Greater, 0.0f),
			TransitionCondition("Yspeed", CompareOp::Less, 0.1f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f),
	}, 0.0f));
	E1_RunState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("E1_Idle", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Less, 0.1f),
			TransitionCondition("Yspeed", CompareOp::Less, 0.1f),
			TransitionCondition("IsGround", CompareOp::True, 0.0f),
	}, 0.0f));
	E1_AttackState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("E1_Idle", std::vector<TransitionCondition>{

	}, 1.0f));
	E1_HurtState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("E1_Idle", std::vector<TransitionCondition>{

	}, 1.0f));

	Enemy_1_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("E1_Attack", std::vector<TransitionCondition>{
		TransitionCondition("Attack", CompareOp::Trigger, 0.0f),
			TransitionCondition("HurtState", CompareOp::False, 0.0f)
	}, 0.0f), 0);
	Enemy_1_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("E1_Hurt", std::vector<TransitionCondition>{
		TransitionCondition("Hurt", CompareOp::Trigger, 0.0f),
	}, 0.0f), 0);

	Enemy_1_animationComponent->AddAnimationState("E1_Idle", E1_IdleState, 0);
	Enemy_1_animationComponent->AddAnimationState("E1_Run", E1_RunState, 0);
	Enemy_1_animationComponent->AddAnimationState("E1_Attack", E1_AttackState, 0);
	Enemy_1_animationComponent->AddAnimationState("E1_Hurt", E1_HurtState, 0);

	Enemy_1_animationComponent->SetScale(1.5f, 0);
	Enemy_1_aiControllerComponent->faceleft = true;
	Enemy_1_collider2DComponent->IsTrigger = false;
	Enemy_1_transformComponent->pos = Vec2(300, 200);
	Enemy_1_rigidBody2DComponent->gravityScale = 50.0f;
	Enemy_1_aiControllerComponent->HandleRun = Enemy_HandleRun;
	Enemy_1_aiControllerComponent->HandleIdle = Enemy_HandleIdle;
	Enemy_1_aiControllerComponent->HandleAttack = Enemy_HandleAttack;
	//加载trigger
	std::unique_ptr<Entity>Enemy_Trigger = GetPrefab("Enemy_Trigger");
	Enemy_1->SetChild(std::move(Enemy_Trigger));
	//加载敌人的sensor
	std::unique_ptr<Entity>Enemy_Eye_Sensor = GetPrefab("Enemy_Eye_Sensor");
	Enemy_1->SetChild(std::move(Enemy_Eye_Sensor));
	std::unique_ptr<Entity>Enemy_Foot_Sensor = GetPrefab("Enemy_Foot_Sensor");
	Enemy_1->SetChild(std::move(Enemy_Foot_Sensor));
	std::unique_ptr<Entity>Enemy_Attack_Sensor = GetPrefab("Enemy_Attack_Sensor");
	Enemy_1->SetChild(std::move(Enemy_Attack_Sensor));


	std::function<void(Entity*, Entity*)>door1_trigger = [](Entity* entityA, Entity* entityB)->void {
		TransformComponent* transformComponent = entityB->GetComponent<TransformComponent>();
		CameraSystem* cameraSystem = World::Instance()->GetCameraSystem();
		cameraSystem->camera->SetPos(4600.0f, 4600.0f);
		transformComponent->pos = Vec2(5000, 5000);
		std::cout << "已经传送" << std::endl;
		};
	std::function<void(Entity*, Entity*)>door2_trigger = [](Entity* entityA, Entity* entityB)->void {
		TransformComponent* transformComponent = entityB->GetComponent<TransformComponent>();
		CameraSystem* cameraSystem = World::Instance()->GetCameraSystem();
		cameraSystem->camera->SetPos(0.0f, 100.0f);
		transformComponent->pos = Vec2(100, 250);
		std::cout << "已经传送" << std::endl;
	};
	//一个传送门
	Entity* door = new Entity("Door");
	PrefabMap["Door"]= std::move(std::unique_ptr<Entity>(door));
	//加载组件
	Collider2DComponent* door_Collider2DComponent = door->AddComponent<Collider2DComponent>(door, Vec2(30, 50), Vec2(0, 10), PhysicsLayer::EnemyTrigger, PhysicsLayer::Player);
	TransformComponent* door_TransformComponent = door->GetComponent<TransformComponent>();
	door_TransformComponent->pos = Vec2(0, 200);
	door_Collider2DComponent->IsTrigger = true;
	door_Collider2DComponent->onTrigger = door1_trigger;

	Entity* door1 = new Entity("Door1");
	PrefabMap["Door1"] = std::move(std::unique_ptr<Entity>(door1));
	//加载组件
	Collider2DComponent* door1_Collider2DComponent = door1->AddComponent<Collider2DComponent>(door1, Vec2(30, 50), Vec2(0, 10), PhysicsLayer::EnemyTrigger, PhysicsLayer::Player);
	TransformComponent* door1_TransformComponent = door1->GetComponent<TransformComponent>();
	door1_TransformComponent->pos = Vec2(4800, 5400);
	door1_Collider2DComponent->IsTrigger = true;
	door1_Collider2DComponent->onTrigger = door2_trigger;
}

void PrefabManager::LoadItems()
{
	//玩家攻击
	std::function<void(Entity* entityA, Entity* entityB)>attack_trigger = [](Entity*entityA,Entity*entityB)->void{
		DamageComponent* From_AttackComponent = entityA->GetComponent<DamageComponent>();
		TagComponent* To_TagComponent = entityB->GetComponent<TagComponent>();
		HpComponent* To_HpComponent = entityB->GetComponent<HpComponent>();
		if (From_AttackComponent == nullptr || To_TagComponent == nullptr)return;
		if (To_TagComponent->tag == Tag::EnemyTag) {
			if (!From_AttackComponent->attackTarget.count(entityA)) {
				AIControllerComponent* aiControllerComponent = entityB->GetComponent<AIControllerComponent>();
				aiControllerComponent->IsHurt = true;
				From_AttackComponent->attackTarget.insert(entityA);
				To_HpComponent->TakeDamage(From_AttackComponent->damage);
			}
		}
	};
	//敌人攻击
	std::function<void(Entity* entityA, Entity* entityB)>E1_attack_trigger = [](Entity* entityA, Entity* entityB)->void {
		DamageComponent* From_AttackComponent = entityA->GetComponent<DamageComponent>();
		TagComponent* To_TagComponent = entityB->GetComponent<TagComponent>();
		HpComponent* To_HpComponent = entityB->GetComponent<HpComponent>();
		if (From_AttackComponent == nullptr || To_TagComponent == nullptr)return;
		if (To_TagComponent->tag == Tag::PlayerTag) {
			if (!From_AttackComponent->attackTarget.count(entityA)) {
				From_AttackComponent->attackTarget.insert(entityA);
				To_HpComponent->TakeDamage(From_AttackComponent->damage);
				PlayerControllerComponent* playerControllerComponent = entityB->GetComponent<PlayerControllerComponent>();
				playerControllerComponent->IsHurt = true;
			}
		}
	};
	//敌人Attack
	Entity* E1_Attack = new Entity("E1_Attack");
	PrefabMap["EItem_Attack_Forward"] = std::move(std::unique_ptr<Entity>(E1_Attack));
	Collider2DComponent* E1_Attack_Forward_Collider_Component = E1_Attack->AddComponent<Collider2DComponent>(E1_Attack, Vec2(20, 25), Vec2(0, 0), PhysicsLayer::EnemyTrigger, PhysicsLayer::Player);
	LifeTimeComponent* E1_Attack_Forward_LifeTime_Component = E1_Attack->AddComponent<LifeTimeComponent>(E1_Attack, 0.5f);
	DamageComponent* E1_Attack_Forward_Damage_Component = E1_Attack->AddComponent<DamageComponent>(E1_Attack, 1, 2.0f);
	E1_Attack_Forward_Collider_Component->IsTrigger = true;
	E1_Attack_Forward_Collider_Component->onTrigger = E1_attack_trigger;
	//AttackForward
	Entity* AttackForward = new Entity("Attack_Forward");
	PrefabMap["PItem_Attack_Forward"] = std::move(std::unique_ptr<Entity>(AttackForward));
	//动画
	std::shared_ptr<Texture>P_Attack_Forward_Texture;
	const std::string P_Attack_Forward_Texture_Path = "Sprites/Player/Attack/AttackForward.png";
	P_Attack_Forward_Texture = resourceManager->LoadTexture(P_Attack_Forward_Texture_Path);
	//动画
	std::shared_ptr<AnimationClip>P_Attack_Forward_Animation = animationClipManager->LoadAnimationClip("PItem_Attack_Forward", P_Attack_Forward_Texture, 2, 1, 2, 0.15f, true);
	std::shared_ptr<AnimationState>P_Attack_Forward_State = std::make_shared<AnimationState>("P_Attack_Forward", P_Attack_Forward_Animation);
	//添加组件
	AnimationComponent* P_Attack_Forward_Animation_Component = AttackForward->AddComponent<AnimationComponent>(AttackForward, 1, std::vector<float>{1.0f}, std::vector<bool>{true}, std::vector<bool>{true});
	Collider2DComponent* P_Attack_Forward_Collider_Component = AttackForward->AddComponent<Collider2DComponent>(AttackForward, Vec2(20, 25), Vec2(0, 0), PhysicsLayer::Default,PhysicsLayer::Enemy);
	LifeTimeComponent* P_Attack_Forward_LifeTime_Component = AttackForward->AddComponent<LifeTimeComponent>(AttackForward, 0.3f);
	DamageComponent* P_Attack_Forward_Damage_Component = AttackForward->AddComponent<DamageComponent>(AttackForward, 1, 2.0f);
	P_Attack_Forward_Collider_Component->IsTrigger = true;
	P_Attack_Forward_Collider_Component->onTrigger = attack_trigger;
	P_Attack_Forward_Animation_Component->AddAnimationState("P_Attack_Forward", P_Attack_Forward_State, 0);
	P_Attack_Forward_Animation_Component->SetScale(0.5f, 0);

	//AttackUp
	Entity* AttackUp = new Entity("Attack_Up");
	PrefabMap["PItem_Attack_Up"] = std::move(std::unique_ptr<Entity>(AttackUp));
	//动画
	std::shared_ptr<Texture>P_Attack_Up_Texture;
	const std::string P_Attack_Up_Texture_Path = "Sprites/Player/Attack/AttackUp.png";
	P_Attack_Up_Texture = resourceManager->LoadTexture(P_Attack_Up_Texture_Path);
	//动画
	std::shared_ptr<AnimationClip>P_Attack_Up_Animation = animationClipManager->LoadAnimationClip("PItem_Attack_Up", P_Attack_Up_Texture, 2, 1, 2, 0.15f, true);
	std::shared_ptr<AnimationState>P_Attack_Up_State = std::make_shared<AnimationState>("P_Attack_Up", P_Attack_Up_Animation);
	//添加组件
	AnimationComponent* P_Attack_Up_Animation_Component = AttackUp->AddComponent<AnimationComponent>(AttackUp, 1, std::vector<float>{1.0f}, std::vector<bool>{true}, std::vector<bool>{true});
	Collider2DComponent* P_Attack_Up_Collider_Component = AttackUp->AddComponent<Collider2DComponent>(AttackUp, Vec2(20, 25), Vec2(0, 10), PhysicsLayer::Default, PhysicsLayer::Enemy);
	LifeTimeComponent* P_Attack_Up_LifeTime_Component = AttackUp->AddComponent<LifeTimeComponent>(AttackUp, 0.3f);
	DamageComponent* P_Attack_Up_Damage_Component = AttackUp->AddComponent<DamageComponent>(AttackUp, 1, 2.0f);
	P_Attack_Up_Collider_Component->IsTrigger = true;
	P_Attack_Up_Collider_Component->onTrigger = attack_trigger;
	P_Attack_Up_Animation_Component->AddAnimationState("P_Attack_Up", P_Attack_Up_State, 0);
	P_Attack_Up_Animation_Component->SetScale(0.5f, 0);

	//AttackDown
	Entity* AttackDown = new Entity("Attack_Down");
	PrefabMap["PItem_Attack_Down"] = std::move(std::unique_ptr<Entity>(AttackDown));
	//动画
	std::shared_ptr<Texture>P_Attack_Down_Texture;
	const std::string P_Attack_Down_Texture_Path = "Sprites/Player/Attack/AttackDown.png";
	P_Attack_Down_Texture = resourceManager->LoadTexture(P_Attack_Down_Texture_Path);
	//动画
	std::shared_ptr<AnimationClip>P_Attack_Down_Animation = animationClipManager->LoadAnimationClip("PItem_Attack_Down", P_Attack_Down_Texture, 2, 1, 2, 0.15f, true);
	std::shared_ptr<AnimationState>P_Attack_Down_State = std::make_shared<AnimationState>("P_Attack_Down", P_Attack_Down_Animation);
	//添加组件
	AnimationComponent* P_Attack_Down_Animation_Component = AttackDown->AddComponent<AnimationComponent>(AttackDown, 1, std::vector<float>{1.0f}, std::vector<bool>{true}, std::vector<bool>{true});
	Collider2DComponent* P_Attack_Down_Collider_Component = AttackDown->AddComponent<Collider2DComponent>(AttackDown, Vec2(20, 25), Vec2(0, 10), PhysicsLayer::Default, PhysicsLayer::Enemy);
	LifeTimeComponent* P_Attack_Down_LifeTime_Component = AttackDown->AddComponent<LifeTimeComponent>(AttackDown, 0.3f);
	DamageComponent* P_Attack_Down_Damage_Component = AttackDown->AddComponent<DamageComponent>(AttackDown, 1, 2.0f);
	P_Attack_Down_Collider_Component->IsTrigger = true;
	P_Attack_Down_Collider_Component->onTrigger = attack_trigger;
	P_Attack_Down_Animation_Component->AddAnimationState("P_Attack_Down", P_Attack_Down_State, 0);
	P_Attack_Down_Animation_Component->SetScale(0.5f, 0);
}

void PrefabManager::LoadSensor()
{
	std::function<void(Entity* entityA, Entity* entityB)>Enemy_Eye_Trigger_Function = [](Entity* entityA, Entity* entityB)->void {
		Collider2DComponent* To_Collider2DComponent = entityB->GetComponent<Collider2DComponent>();
		Entity* parent = entityA->GetComponent<TransformComponent>()->parent->GetOwner();
		Vec2 dis = entityB->GetComponent<TransformComponent>()->worldpos - parent->GetComponent<TransformComponent>()->worldpos;
		AIControllerComponent* aiControllerComponent = parent->GetComponent<AIControllerComponent>();
		aiControllerComponent->visionSensor.push_back({ entityB,dis });
	};
	std::function<void(Entity* entityA, Entity* entityB)>Enemy_Foot_Trigger_Function = [](Entity* entityA, Entity* entityB)->void {
		Collider2DComponent* To_Collider2DComponent = entityB->GetComponent<Collider2DComponent>();
		Entity* parent = entityA->GetComponent<TransformComponent>()->parent->GetOwner();
		Vec2 dis = entityB->GetComponent<TransformComponent>()->worldpos - parent->GetComponent<TransformComponent>()->worldpos;
		AIControllerComponent* aiControllerComponent = parent->GetComponent<AIControllerComponent>();
		aiControllerComponent->footSensor.push_back({ entityB,dis });
	};
	std::function<void(Entity* entityA, Entity* entityB)>Enemy_Attack_Trigger_Function = [](Entity* entityA, Entity* entityB)->void {
		TagComponent* To_TagComponent = entityB->GetComponent<TagComponent>();
		if (!To_TagComponent||To_TagComponent->tag != Tag::PlayerTag)return;
		Collider2DComponent* To_Collider2DComponent = entityB->GetComponent<Collider2DComponent>();
		Entity* parent = entityA->GetComponent<TransformComponent>()->parent->GetOwner();
		AIControllerComponent* aiControllerComponent = parent->GetComponent<AIControllerComponent>();
		aiControllerComponent->playerInAttackRange = true;
	};
	std::function<void(Entity* entityA, Entity* entityB)>Enemy_Trigger_Function = [](Entity* entityA, Entity* entityB)->void {
		DamageComponent* From_AttackComponent = entityA->GetComponent<DamageComponent>();
		TagComponent* To_TagComponent = entityB->GetComponent<TagComponent>();
		HpComponent* To_HpComponent = entityB->GetComponent<HpComponent>();
		if (From_AttackComponent == nullptr || To_TagComponent == nullptr)return;
		if (To_TagComponent->tag == Tag::PlayerTag) {
			if (!From_AttackComponent->attackTarget.count(entityA)) {
				From_AttackComponent->attackTarget.insert(entityA);
				To_HpComponent->TakeDamage(From_AttackComponent->damage);
				PlayerControllerComponent* playerControllerComponent = entityB->GetComponent<PlayerControllerComponent>();
				playerControllerComponent->IsHurt = true;
			}
		}
		};

	Entity* Enemy_Eye_Sensor = new Entity("Enemy_Eye_Sensor");
	PrefabMap["Enemy_Eye_Sensor"] = std::move(std::unique_ptr<Entity>(Enemy_Eye_Sensor));
	Collider2DComponent* Enemy_Eye_Sensor_collider2DComponent = Enemy_Eye_Sensor->AddComponent<Collider2DComponent>(Enemy_Eye_Sensor, Vec2(120, 10), Vec2(0, 0), PhysicsLayer::Default, PhysicsLayer::Player | PhysicsLayer::Wall);
	AISensorController* Enemy_Eye_Sensor_aisensorController = Enemy_Eye_Sensor->AddComponent<AISensorController>(Enemy_Eye_Sensor);
	TransformComponent* Enemy_Eye_Sensor_transformComponent = Enemy_Eye_Sensor->GetComponent<TransformComponent>();
	TagComponent* Enemy_Eye_Sensor_tagComponent = Enemy_Eye_Sensor->AddComponent<TagComponent>(Enemy_Eye_Sensor, Tag::SensorTag);
	Enemy_Eye_Sensor_transformComponent->pos = Vec2(80.0f, 0.0f);
	Enemy_Eye_Sensor_collider2DComponent->IsTrigger = true;
	Enemy_Eye_Sensor_collider2DComponent->onTrigger = Enemy_Eye_Trigger_Function;

	Entity* Enemy_Foot_Sensor = new Entity("Enemy_Foot_Sensor");
	PrefabMap["Enemy_Foot_Sensor"] = std::move(std::unique_ptr<Entity>(Enemy_Foot_Sensor));
	Collider2DComponent* Enemy_Foot_Sensor_collider2DComponent = Enemy_Foot_Sensor->AddComponent<Collider2DComponent>(Enemy_Foot_Sensor, Vec2(20, 30), Vec2(0, 0), PhysicsLayer::Default, PhysicsLayer::Wall);
	AISensorController* Enemy_Foot_Sensor_aisensorController = Enemy_Foot_Sensor->AddComponent<AISensorController>(Enemy_Foot_Sensor);
	TransformComponent* Enemy_Foot_Sensor_transformComponent = Enemy_Foot_Sensor->GetComponent<TransformComponent>();
	TagComponent* Enemy_Foot_Sensor_tagComponent = Enemy_Foot_Sensor->AddComponent<TagComponent>(Enemy_Foot_Sensor, Tag::SensorTag);
	Enemy_Foot_Sensor_transformComponent->pos = Vec2(30.0f, 40.0f);
	Enemy_Foot_Sensor_collider2DComponent->IsTrigger = true;
	Enemy_Foot_Sensor_collider2DComponent->onTrigger = Enemy_Foot_Trigger_Function;

	Entity* Enemy_Attack_Sensor = new Entity("Enemy_Attack_Sensor");
	PrefabMap["Enemy_Attack_Sensor"] = std::move(std::unique_ptr<Entity>(Enemy_Attack_Sensor));
	Collider2DComponent* Enemy_Attack_Sensor_collider2DComponent = Enemy_Attack_Sensor->AddComponent<Collider2DComponent>(Enemy_Attack_Sensor, Vec2(20, 20), Vec2(0, 0), PhysicsLayer::Default, PhysicsLayer::Wall|PhysicsLayer::Player);
	AISensorController* Enemy_Attack_Sensor_aisensorController = Enemy_Attack_Sensor->AddComponent<AISensorController>(Enemy_Attack_Sensor);
	TransformComponent* Enemy_Attack_Sensor_transformComponent = Enemy_Attack_Sensor->GetComponent<TransformComponent>();
	TagComponent* Enemy_Attack_Sensor_tagComponent = Enemy_Attack_Sensor->AddComponent<TagComponent>(Enemy_Attack_Sensor, Tag::SensorTag);
	Enemy_Attack_Sensor_transformComponent->pos = Vec2(20.0f, 20.0f);
	Enemy_Attack_Sensor_collider2DComponent->IsTrigger = true;
	Enemy_Attack_Sensor_collider2DComponent->onTrigger = Enemy_Attack_Trigger_Function;

	//加载敌人子物体的trigger
	Entity* Enemy_Trigger = new Entity("Enemy_Trigger");
	//加载物理组件
	PrefabMap["Enemy_Trigger"] = std::move(std::unique_ptr<Entity>(Enemy_Trigger));
	Collider2DComponent* Enemy_Trigger_collider2DComponent = Enemy_Trigger->AddComponent<Collider2DComponent>(Enemy_Trigger, Vec2(30, 40), Vec2(0, 0), PhysicsLayer::EnemyTrigger, PhysicsLayer::Player);
	TransformComponent* Enemy_Trigger_transformComponent = Enemy_Trigger->GetComponent<TransformComponent>();
	DamageComponent* Enemy_Trigger_Damage_Component = Enemy_Trigger->AddComponent<DamageComponent>(Enemy_Trigger, 1, 5.0f);
	Enemy_Trigger_transformComponent->pos = Vec2(0, 10);
	Enemy_Trigger_collider2DComponent->onTrigger = Enemy_Trigger_Function;
	Enemy_Trigger_collider2DComponent->IsTrigger = true;
}
