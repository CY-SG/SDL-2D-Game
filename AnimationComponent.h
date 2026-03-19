#pragma once
#include"Component.h"
#include"memory"
#include<string>
#include<vector>
class AnimationPlay;
class AnimationController;
class AnimationState;
class AnimationTransition;
class AnimatorParam;
class Render;
class Camera2D;
class AnimationLayer;
class AnimationComponent :public Component {
public:
	AnimationComponent(Entity* entity,int size,std::vector<float>weights,std::vector<bool>overrides, std::vector<bool>actives);
	AnimationComponent(Entity*entity);
	void Update() override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	void SetTrigger(const std::string& name,int layer);
	void SetBool(const std::string& name, bool value, int layer);
	void SetFloat(const std::string& name, float value, int layer);
	void SetStartState(const std::string& name, int layer);
	void SetFlip(bool _flip);
	void SetScale(float _scale, int layer);
	void SetActive(bool active, int layer);
	void AddAnimationState(const std::string& name, std::shared_ptr<AnimationState> state, int layer);
	void AddFromAnyTransition(std::shared_ptr<AnimationTransition> _transition, int layer);
	void AddAnimationParam(const std::string& name, AnimatorParam param, int layer);
	void RenderAnimation(Render* render, int x, int y);
	void RenderAnimationWithCamera(Render* render, Camera2D* camera, int x, int y);

	bool GetActive(int layer);
private:
	void UpdateAnimationPlay();
	AnimationPlay* animationPlay;
	std::vector<std::unique_ptr<AnimationLayer>>animationLayer;
	int size;
};