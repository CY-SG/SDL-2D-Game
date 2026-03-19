#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include"AnimationTransition.h"
#include"TransitionCondition.h"
#include"AnimationState.h"
class AnimationPlay;
class AnimationState;
class AnimationTransition;
class AnimationController {
public:
	void Init(AnimationPlay* _animationPlay);
	void SetStartState(const std::string& name);
	void AddAnimationState(const std::string& name, std::shared_ptr<AnimationState>state);
	inline void AddFromAnyTransition(std::shared_ptr<AnimationTransition>_transition) {
		FromAnyTransition.push_back(std::move(_transition));
	}
	void AddAnimationParam(const std::string& name, AnimatorParam param);
	void SetTrigger(const std::string& name);
	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);
	void Update();
	AnimationController* Clone();
private:
	void ChangeToState(const std::string& name);
	int CheckFromAny();
	bool CheckTransition(AnimationTransition* transition);
	void ConsumeTrigger(AnimationTransition* transition);
	AnimationPlay* animationPlay;
	AnimationState* currentState;
	std::unordered_map<std::string, std::shared_ptr<AnimationState>>animationStates;
	std::unordered_map<std::string, AnimatorParam>animationParams;
	std::vector<std::shared_ptr<AnimationTransition>>FromAnyTransition;
};