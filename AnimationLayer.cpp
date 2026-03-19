#include"AnimationLayer.h"
#include"AnimationController.h"
#include"AnimationPlay.h"
AnimationLayer::AnimationLayer(int index,float weight,bool _override, bool _active):layer(index),weight(weight),_override(_override),active(_active) {
	animationController = std::make_unique<AnimationController>();
	animationPlay = std::make_unique<AnimationPlay>();
	animationController.get()->Init(animationPlay.get());
}

AnimationLayer* AnimationLayer::Clone()
{
	AnimationLayer* _clone = new AnimationLayer(layer, weight, _override, active);
	_clone->animationPlay = std::move(std::unique_ptr<AnimationPlay>(animationPlay.get()->Clone()));
	_clone->animationController = std::move(std::unique_ptr<AnimationController>(animationController.get()->Clone()));
	_clone->animationController.get()->Init(_clone->animationPlay.get());
	return _clone;
}

int AnimationLayer::GetLayer()
{
	return layer;
}

float AnimationLayer::GetWeight()
{
	return weight;
}

bool AnimationLayer::GetIsOverride()
{
	return _override;
}

bool AnimationLayer::GetIsActive()
{
	return active;
}

void AnimationLayer::SetActive(bool _active)
{
	active = _active;
}
