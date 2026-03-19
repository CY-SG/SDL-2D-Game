#pragma once
#include"Component.h"
class AnimationComponent;
class InputComponent;
class RigidBody2DComponent;
class CameraSystem;
class ControllerComponent :public Component {
public:
	void Update()override;
	ControllerComponent(Entity* entity);
	virtual ~ControllerComponent() = default;
	std::unique_ptr<Component>Clone(Entity* entity) = 0;
	void SetXSpeed(bool MoveLeft);
	void SetYSpeed();
	void SetXSpeed(float Xspeed);
	InputComponent* inputComponent;
protected:
	CameraSystem* cameraSystem;
	AnimationComponent* animationComponent;
	RigidBody2DComponent* rigidBody2DComponent;
};