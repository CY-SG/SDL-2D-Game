#include "InitEntity.h"
#include"AnimationClipManager.h"
#include"SDLResourceManager.h"
#include"AnimationComponent.h"
#include"RigidBody2DComponent.h"
#include"InputComponent.h"
#include"Collider2DComponent.h"
#include"TransformComponent.h"
#include"MoveComponent.h"
#include"JumpComponent.h"
#include"AnimationState.h"
#include"PlayerControllerComponent.h"
#include"StateMachine.h"
#include"PSlideState.h"
#include"MoveStateMachine.h"
#include"ActionStateMachine.h"
#include"PNoneState.h"
#include"PAttackForwardState.h"
#include"PNormalState.h"
#include"PAttackDownState.h"
#include"PAttackUpState.h"
#include<memory>
#include"SDLInput.h"
#include"Entity.h"
void InitEntity::LoadResource(ResourceManager* resourceManager, AnimationClipManager* animationClipManager)
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
		P_RunLoop_Texture[i-3] = resourceManager->LoadTexture(path);
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
	//加载Player相关组件

	Entity* player = new Entity(0);
	EntityMap["Player"] = player;
	SDLInput* P_Input = new SDLInput();
	std::vector<JumpState>P_Jump = { {150.0f,0.5f,true},{200.0f,0.0f,false} };
	//组件
	RigidBody2DComponent* P_rigidBody2DComponent = player->AddComponent<RigidBody2DComponent>(player);
	Collider2DComponent* P_collider2DComponent = player->AddComponent<Collider2DComponent>(player, Vec2(40, 50), Vec2(0, 10),PhysicsLayer::Default);
	AnimationComponent* P_animationComponent = player->AddComponent<AnimationComponent>(player, 2, std::vector<float>{1.0f, 1.0f}, std::vector<bool>{true, true}, std::vector<bool>{true,false});
	InputComponent* P_inputComponent = player->AddComponent<InputComponent>(player,P_Input);
	MoveComponent* P_moveComponent = player->AddComponent<MoveComponent>(player,150.0f);
	JumpComponent* P_jumpComponent = player->AddComponent<JumpComponent>(player, 2, P_Jump);
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
	P_controllerComponent->AddState(StateType::MoveState,"P_Normal", std::move(P_NormalState_Machine));
	P_controllerComponent->AddState(StateType::MoveState,"P_Slide", std::move(P_SlideState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_None", std::move(P_NoneState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackForward", std::move(P_AttackForwardState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackUp", std::move(P_AttackUpState_Machine));
	P_controllerComponent->AddState(StateType::ActionState, "P_AttackDown", std::move(P_AttackDownState_Machine));
	P_controllerComponent->SetStateStart(StateType::MoveState,"P_Normal");
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
	//动画绑定clip
	//Move动画
	std::shared_ptr<AnimationState>P_IdleState = std::make_shared<AnimationState>("P_Idle", P_Idle_Animation);
	std::shared_ptr<AnimationState>P_RunStartState = std::make_shared<AnimationState>("P_RunStart", P_RunStart_Animation);
	std::shared_ptr<AnimationState>P_RunLoopState = std::make_shared<AnimationState>("P_RunLoop", P_RunLoop_Animation);
	std::shared_ptr<AnimationState>P_JumpDownState = std::make_shared<AnimationState>("P_JumpDown", P_JumpDown_Animation);
	std::shared_ptr<AnimationState>P_JumpUpState=std::make_shared<AnimationState>("P_JumpUp", P_JumpUp_Animation);
	std::shared_ptr<AnimationState>P_TwoJumpState = std::make_shared<AnimationState>("P_TwoJump", P_TwoJump_Animation);
	std::shared_ptr<AnimationState>P_SlideState = std::make_shared<AnimationState>("P_Slide", P_Slide_Animation);
	std::shared_ptr<AnimationState>P_SlideJumpState = std::make_shared<AnimationState>("P_SlideJump", P_SlideJump_Animation);
	//Action动画
	std::shared_ptr<AnimationState>P_AttackLeftState = std::make_shared<AnimationState>("P_AttackLeft", P_AttackLeft_Animation);
	std::shared_ptr<AnimationState>P_AttackRightState = std::make_shared<AnimationState>("P_AttackRight", P_AttackRight_Animation);
	std::shared_ptr<AnimationState>P_AttackUpState = std::make_shared<AnimationState>("P_AttackUp", P_AttackUp_Animation);
	std::shared_ptr<AnimationState>P_AttackDownState = std::make_shared<AnimationState>("P_AttackDown", P_AttackDown_Animation);
	std::shared_ptr<AnimationState>P_NoneState = std::make_shared<AnimationState>("P_None", nullptr);
	//设置动画状态机
	//Move层
	P_IdleState.get()->AddAnimationTransition(std::make_shared<AnimationTransition>("P_RunStart", std::vector<TransitionCondition>{
		TransitionCondition("Xspeed", CompareOp::Greater, 0.0f),
		TransitionCondition("Yspeed", CompareOp::Less, 0.1f),
		TransitionCondition("IsGround", CompareOp::True, 0.0f),
		TransitionCondition("RunStart",CompareOp::Trigger,0.0f)
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
		TransitionCondition("Xspeed",CompareOp::Greater,0.0f),
		TransitionCondition("Yspeed",CompareOp::Same,0.0f),
		TransitionCondition("IsGround",CompareOp::True,0.0f)
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
		TransitionCondition("SlideJump",CompareOp::Trigger,0.0f)
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

	//Any->Attack-Left
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackLeft", std::vector<TransitionCondition>{
		TransitionCondition("FaceLeft",CompareOp::True,0.0f),
		TransitionCondition("AttackForward",CompareOp::Trigger,0.0f)
	}, 0.0f),1);
	//Any->Attack-Right
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackRight", std::vector<TransitionCondition>{
		TransitionCondition("FaceLeft",CompareOp::False,0.0f),
		TransitionCondition("AttackForward",CompareOp::Trigger,0.0f)
	}, 0.0f), 1);
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackUp", std::vector<TransitionCondition>{
		TransitionCondition("AttackUp", CompareOp::Trigger, 0.0f)
	}, 0.0f), 1);
	P_animationComponent->AddFromAnyTransition(std::make_shared<AnimationTransition>("P_AttackDown", std::vector<TransitionCondition>{
		TransitionCondition("AttackDown", CompareOp::Trigger, 0.0f)
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

	P_animationComponent->SetStartState("P_Idle", 0);
	P_animationComponent->SetStartState("P_None", 1);
	//下面墙体
	Entity* Wall_1 = new Entity(1);
	EntityMap["Wall_1"] = Wall_1;
	//物理组件
	Collider2DComponent* Wall_1_collider2DComponent = Wall_1->AddComponent<Collider2DComponent>(Wall_1, Vec2(200, 30), Vec2(0, 0),PhysicsLayer::Wall);
	TransformComponent* Wall_1_transformComponent = Wall_1->GetComponent<TransformComponent>();
	Wall_1_transformComponent->pos = Vec2(50, 300);

	//左边墙体
	Entity* Wall_2 = new Entity(2);
	EntityMap["Wall_2"] = Wall_2;
	//物理组件
	Collider2DComponent* Wall_2_collider2DComponent = Wall_2->AddComponent<Collider2DComponent>(Wall_2, Vec2(10, 300), Vec2(0, 0), PhysicsLayer::Wall);
	TransformComponent* Wall_2_transformComponent = Wall_2->GetComponent<TransformComponent>();
	Wall_2_transformComponent->pos = Vec2(-80, 150);
}


Entity* InitEntity::GetEntity(const std::string& name)
{
	return EntityMap[name];
}
