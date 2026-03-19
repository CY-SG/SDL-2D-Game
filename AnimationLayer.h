#pragma once
#include<memory>
#include<string>
class AnimationController;
class AnimationPlay;
class AnimationState;
class AnimationTransition;
class AnimatorParam;
class AnimationLayer {
public:
	AnimationLayer(int index,float weight,bool _override,bool _active);
	AnimationLayer* Clone();
	int GetLayer();
	float GetWeight();
	bool GetIsOverride();
	bool GetIsActive();
	void SetActive(bool _active);
	std::unique_ptr<AnimationController>animationController;
	std::unique_ptr<AnimationPlay>animationPlay;
private:
	int layer;
	float weight;
	bool _override;
	bool active;
};