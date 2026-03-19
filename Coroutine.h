#pragma once
#include<functional>
#include<vector>
#include<string>
class Entity;
struct CoroutineStep {
	float startTime;
	float duration;
	std::function<void(Entity*)> onEnter;
	std::function<void(Entity*, float time)>update;
	std::function<void(Entity*)> onExit;
	bool entered = false;
	CoroutineStep(float _startTime, float _duration, std::function<void(Entity*)> _onEnter = nullptr, std::function<void(Entity*,float)>_update = nullptr, std::function<void(Entity*)>_onExit = nullptr);
};

class Coroutine {
public:
	void Update();
	Coroutine(Entity* _owner,int _id,const std::string& group, std::vector<CoroutineStep> _steps);
	void AddCoroutine(CoroutineStep step);
	std::vector<CoroutineStep>steps;
	Entity* owner;
	float currTime;
	std::string group;
	int id;
	bool IsFinish;
	float endTime;
};