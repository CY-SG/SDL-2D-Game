#pragma once
#include"AnimationFrame.h"
#include<vector>
class AnimationClip {
public:
	void AddFrame(const Sprite& sprite, float duration,bool loop);
	const AnimationFrame& GetFrame(int index);
	int GetFrameCount();
	bool GetLoop();
	float GetTotalTime();
private:
	std::vector<AnimationFrame>frames;
	bool loop;
	float totalTime = 0;
};