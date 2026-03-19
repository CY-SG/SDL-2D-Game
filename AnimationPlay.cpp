#include "AnimationPlay.h"
#include"AnimationClip.h"
#include"EngineTime.h"
#include"Render.h"
#include"Rect.h"
#include<iostream>
AnimationPlay::AnimationPlay()
{
}
void AnimationPlay::Update()
{
	if (!animationClip || !playing)return;
	float time= EngineTime::deltaTime();
	currentTime += time;
	animationTime += time;
	const AnimationFrame& frame = animationClip->GetFrame(currentFrame);
	if (currentTime >= frame.duration) {
		currentTime -= frame.duration;
		currentFrame++;
		if (currentFrame >= animationClip->GetFrameCount()) {
			if (loop)currentFrame = 0;
			else {
				currentFrame -= 1;
				playing = false;
			}
		}
	}
}

AnimationPlay* AnimationPlay::Clone()
{
	AnimationPlay* _clone = new AnimationPlay();
	_clone->scale = scale;
	_clone->animationTime = 0.0f;
	_clone->loop = false;
	_clone->flip = false;
	_clone->playing = false;
	_clone->animationClip = nullptr;
	_clone->currentTime = 0;
	_clone->currentFrame = 0;
	return _clone;
}

void AnimationPlay::Play(AnimationClip* clip)
{
	if (!clip)return;
	animationClip = clip;
	this->loop = clip->GetLoop();
	currentFrame = 0;
	currentTime = 0.0f;
	animationTime = 0.0f;
	playing = true;
}

void AnimationPlay::Stop()
{
	playing = false;
}

void AnimationPlay::RenderAnimation(Render* render, int x, int y)
{
	if (!animationClip || !playing)return;
	render->DrawSprite(&(animationClip->GetFrame(currentFrame).sprite), x,y, scale, flip);
}

void AnimationPlay::SetFlip(bool _flip)
{
	flip = _flip;
}

void AnimationPlay::SetScale(float _scale)
{
	scale = _scale;
}

float AnimationPlay::GetNormalizedTime() const
{
	if (!animationClip)return 0.0f;
	return animationTime / animationClip->GetTotalTime();
}

AnimationClip* AnimationPlay::GetAnimationClip() const
{
	if (!animationClip)return nullptr;
	return animationClip;
}
