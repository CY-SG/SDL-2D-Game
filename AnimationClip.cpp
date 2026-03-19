#include "AnimationClip.h"

void AnimationClip::AddFrame(const Sprite& sprite, float duration,bool loop)
{
    frames.push_back(AnimationFrame(sprite, duration));
    this->loop = loop;
    totalTime += duration;
}

const AnimationFrame& AnimationClip::GetFrame(int index)
{
    return frames[index];
}

int AnimationClip::GetFrameCount()
{
    return frames.size();
}

bool AnimationClip::GetLoop()
{
    return loop;
}

float AnimationClip::GetTotalTime()
{
    return totalTime;
}
