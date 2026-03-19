#include "AnimationComponent.h"
#include"AnimationController.h"
#include"AnimationPlay.h"
#include"Entity.h"
#include"Camera2D.h"
#include"AnimationLayer.h"
#include"AnimationState.h"
AnimationComponent::AnimationComponent(Entity* entity,int size, std::vector<float>weights, std::vector<bool>overrides,std::vector<bool>actives):size(size)
{
	SetOwner(entity);
	animationLayer.resize(size);
	for (int i = 0; i < size; i++) {
		animationLayer[i] = std::make_unique<AnimationLayer>(i, weights[i], overrides[i],actives[i]);
	}
	animationPlay = nullptr;
}

AnimationComponent::AnimationComponent(Entity* entity)
{
	SetOwner(entity);
}

void AnimationComponent::Update()
{
	for (int i = 0; i < size; i++) {
		animationLayer[i].get()->animationController.get()->Update();
		animationLayer[i].get()->animationPlay.get()->Update();
	}
	UpdateAnimationPlay();
}

std::unique_ptr<Component> AnimationComponent::Clone(Entity* entity)
{

	std::unique_ptr<AnimationComponent>_clone = std::make_unique<AnimationComponent>(entity);
	_clone.get()->animationLayer.resize(size);
	_clone.get()->animationPlay = nullptr;
	_clone.get()->size = size;
	for (int i = 0; i < size; i++) {
		_clone.get()->animationLayer[i] = std::move(std::unique_ptr<AnimationLayer>(animationLayer[i].get()->Clone()));
	}
	return _clone;
}

void AnimationComponent::SetTrigger(const std::string& name, int layer)
{
	animationLayer[layer].get()->animationController.get()->SetTrigger(name);
}

void AnimationComponent::SetBool(const std::string& name, bool value, int layer)
{
	animationLayer[layer].get()->animationController.get()->SetBool(name, value);
}

void AnimationComponent::SetFloat(const std::string& name, float value, int layer)
{
	animationLayer[layer].get()->animationController.get()->SetFloat(name, value);
}

void AnimationComponent::SetStartState(const std::string& name, int layer)
{
	animationLayer[layer].get()->animationController.get()->SetStartState(name);
}

void AnimationComponent::SetFlip(bool _flip)
{
	for(int i=0;i<size;i++)
	animationLayer[i].get()->animationPlay.get()->SetFlip(_flip);
}

void AnimationComponent::SetScale(float _scale, int layer)
{
	animationLayer[layer].get()->animationPlay.get()->SetScale(_scale);
}

void AnimationComponent::SetActive(bool active, int layer)
{
	animationLayer[layer].get()->SetActive(active);
}

void AnimationComponent::AddAnimationState(const std::string& name, std::shared_ptr<AnimationState> state, int layer)
{
	animationLayer[layer].get()->animationController.get()->AddAnimationState(name, std::move(state));
}

void AnimationComponent::AddFromAnyTransition(std::shared_ptr<AnimationTransition> _transition, int layer)
{
	animationLayer[layer].get()->animationController.get()->AddFromAnyTransition(_transition);
}

void AnimationComponent::AddAnimationParam(const std::string& name, AnimatorParam param, int layer)
{
	animationLayer[layer].get()->animationController.get()->AddAnimationParam(name, param);
}

void AnimationComponent::RenderAnimation(Render* render, int x, int y)
{
	if(animationPlay)
	animationPlay->RenderAnimation(render, x, y);
}

void AnimationComponent::RenderAnimationWithCamera(Render* render, Camera2D* camera, int x, int y)
{
	if (animationPlay) {
		Vec2 screenPos = camera->WorldToScreen(Vec2(x, y));
		animationPlay->RenderAnimation(render, screenPos.x, screenPos.y);
	}
}

bool AnimationComponent::GetActive(int layer)
{
	return animationLayer[layer].get()->GetIsActive();
}

void AnimationComponent::UpdateAnimationPlay()
{
	for (int i = size - 1; i >=0; i--) {
		auto t = animationLayer[i].get();
		if (!t->GetIsActive())continue;
		if (t->GetIsOverride()) { 
			animationPlay = t->animationPlay.get();
			return;
		}
	}
}
