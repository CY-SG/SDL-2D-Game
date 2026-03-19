#include "AnimationController.h"
#include"AnimationPlay.h"
#include"AnimationState.h"
void AnimationController::Init(AnimationPlay* _animationPlay)
{
	animationPlay = _animationPlay;
}

void AnimationController::SetStartState(const std::string& name)
{
	AnimationState* t = animationStates[name].get();
	currentState = t;
	animationPlay->Play(t->GetAnimationClip().get());
}

void AnimationController::AddAnimationState(const std::string& name, std::shared_ptr<AnimationState> state)
{
	animationStates[name] = std::move(state);
}

//void AnimationController::AddFromAnyTransition(const std::string& name, const std::shared_ptr<AnimationTransition> _transition)
//{
//	FromAnyTransition.push_back(_transition);
//}

void AnimationController::AddAnimationParam(const std::string& name, AnimatorParam param)
{
	animationParams[name] = param;
}

void AnimationController::SetTrigger(const std::string& name)
{
	animationParams[name].triggerValue = true;
}

void AnimationController::SetBool(const std::string& name, bool value)
{
	animationParams[name].boolValue = value;
}

void AnimationController::SetFloat(const std::string& name, float value)
{
	animationParams[name].floatValue = value;
}

void AnimationController::Update()
{
	if (!currentState) return;
	int index = CheckFromAny();
	if (index != -1) {
		auto& p = FromAnyTransition[index];
		ConsumeTrigger(p.get());
		ChangeToState(p.get()->to);
		return;
	}
	for (auto& p : currentState->GetAnimationTransition()) {
		if (CheckTransition(p)) {
			ConsumeTrigger(p);
			ChangeToState(p->to);
			return;
		}
	}
}

AnimationController* AnimationController::Clone()
{
	AnimationController* _clone = new AnimationController();
	for (auto& t : FromAnyTransition) {
		_clone->FromAnyTransition.push_back(t);
	}
	for (auto&t: animationParams) {
		_clone->animationParams[t.first] = t.second;
	}
	for (auto& t : animationStates) {
		_clone->animationStates[t.first] = t.second;
	}
	_clone->animationPlay = nullptr;
	_clone->currentState = nullptr;
	return _clone;
}

void AnimationController::ChangeToState(const std::string& name)
{
	if (name == currentState->name)return;
	AnimationState*t = animationStates[name].get();
	currentState = t;
	animationPlay->Play(t->GetAnimationClip().get());
}

int AnimationController::CheckFromAny()
{
	for (int i = 0; i < FromAnyTransition.size(); i++) {
		auto& p = FromAnyTransition[i];
		if (CheckTransition(p.get()))return i;
	}
	return -1;
}

bool AnimationController::CheckTransition(AnimationTransition* transition)
{
	if (animationPlay->GetNormalizedTime() < transition->exitTime)return false;
	std::vector<TransitionCondition>& p = transition->transitionConditions;
	for (auto& t : p) {
		if (t.compareOp == CompareOp::ExitTime)continue;
		auto& params = animationParams[t.name];
		CompareOp compareOp = t.compareOp;
		ParamType type = params.type;
		switch (type) {
		case ParamType::Bool:
			if ((compareOp == CompareOp::True && params.boolValue == false) || (compareOp == CompareOp::False && params.boolValue == true))
				return false;
			break;
		case ParamType::Trigger:
			if (!params.triggerValue)
				return false;
			break;
		case ParamType::Float:
			if (compareOp == CompareOp::Greater) {
				if (params.floatValue <= t.value)return false;
			}
			else if (compareOp == CompareOp::Less) {
				if (params.floatValue >= t.value)return false;
			}
			else if (compareOp == CompareOp::NotSame) {
				if (params.floatValue == t.value)return false;
			}
			else if (compareOp == CompareOp::Same) {
				if (params.floatValue != t.value)return false;
			}
			break;
		}
	}
	return true;
}

void AnimationController::ConsumeTrigger(AnimationTransition* transition)
{
	auto& p = transition->transitionConditions;
	for (auto& t : p) {
		auto& m = animationParams[t.name];
		if (m.type == ParamType::Trigger) {
			m.triggerValue = false;
		}
	}
}