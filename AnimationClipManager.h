#pragma once
#include<unordered_map>
#include<memory>
#include<string>
#include"AnimationClip.h"
#include<vector>
class Texture;
class AnimationClipManager {
public:
	std::shared_ptr<AnimationClip>LoadAnimationClip(const std::string& name,std::shared_ptr<Texture>texture,int n,int i,int j, float duration,bool loop);
	std::shared_ptr<AnimationClip>GetAnimationClip(const std::string& name);
	std::shared_ptr<AnimationClip>LoadAnimationClip(const std::string& name,std::vector<std::shared_ptr<Texture>>texture, float duration, bool loop);
private:
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>>animationClipMap;
};