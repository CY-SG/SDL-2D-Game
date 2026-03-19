#pragma once
class AnimationClip;
class Render;
class Rect;
class AnimationPlay {
public:
	AnimationPlay();
	void Update();
	AnimationPlay* Clone();
	void Play(AnimationClip* clip);
	void Stop();
	void RenderAnimation(Render* render,int x,int y);
	void SetFlip(bool _flip);
	void SetScale(float _scale);
	float GetNormalizedTime() const;
	AnimationClip* GetAnimationClip()const;
private:
	AnimationClip* animationClip = nullptr;
	float currentTime = 0.0f;
	float animationTime = 0.0f;
	int currentFrame = 0;
	bool loop = true;
	bool playing = false;
	bool flip = false;
	float scale = 1.0f;
};