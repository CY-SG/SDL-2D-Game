#pragma once
#include<string>
#include<vector>
#include"TransitionCondition.h"
struct AnimationTransition {
	std::string to;
	std::vector<TransitionCondition>transitionConditions;
	float exitTime;
	AnimationTransition(const std::string& _to, std::vector<TransitionCondition>_transitionConditions, float _exitTime) {
		to = _to;
		transitionConditions = _transitionConditions;
		exitTime = _exitTime;
	}
};