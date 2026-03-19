#pragma once
#include<string>
#include<memory>
#include"AnimationTransition.h"
class AnimationClip;
class AnimationState {
public:
	std::string name;
	AnimationState(const std::string& _name, std::shared_ptr<AnimationClip>_animationClip);
	std::shared_ptr<AnimationClip>GetAnimationClip();
	std::vector<AnimationTransition*>GetAnimationTransition();
	inline void AddAnimationTransition(std::shared_ptr<AnimationTransition>transition) {
		animationTransition.push_back(std::move(transition));
	}
private:
	std::shared_ptr<AnimationClip>animationClip;
	std::vector<std::shared_ptr<AnimationTransition>>animationTransition;
};