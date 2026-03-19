#include "AnimationState.h"
#include"AnimationClip.h"
AnimationState::AnimationState(const std::string& _name, std::shared_ptr<AnimationClip> _animationClip)
{
    name = _name;
    animationClip = _animationClip;
}

std::shared_ptr<AnimationClip> AnimationState::GetAnimationClip()
{
    return animationClip;
}

std::vector<AnimationTransition*> AnimationState::GetAnimationTransition()
{
    std::vector<AnimationTransition*>result(animationTransition.size());
    for (int i = 0; i < animationTransition.size(); i++)result[i] = animationTransition[i].get();
    return result;
}
