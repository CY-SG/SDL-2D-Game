#include "Coroutine.h"
#include"EngineTime.h"
void Coroutine::Update()
{
    for (auto& t : steps) {
        if (currTime >= t.startTime && currTime <= t.startTime + t.duration) {
            if (!t.entered)
            {
                t.entered = true;
                if (t.onEnter) t.onEnter(owner);
            }
            if(t.update)
            t.update(owner, currTime - t.startTime);
        }
        else {
            if (t.entered)
            {
                t.entered = false;
                if (t.onExit) t.onExit(owner);
            }
        }
    }
    if (currTime >= endTime)IsFinish = true;
}

Coroutine::Coroutine(Entity* _owner, int _id, const std::string& group, std::vector<CoroutineStep> _steps)
{
    this->owner = _owner;
    this->steps = _steps;
    this->id = _id;
    this->group = group;
    IsFinish = false;
    currTime = 0.0f;
    endTime = 0.0f;
    for (auto& s : steps)
    {
        endTime = std::max(endTime,
            s.startTime + s.duration);
    }
}

void Coroutine::AddCoroutine(CoroutineStep step)
{
    steps.push_back(step);
}

CoroutineStep::CoroutineStep(float _startTime, float _duration, std::function<void(Entity*)> _onEnter, std::function<void(Entity*,float)> _update, std::function<void(Entity*)> _onExit)
{
    this->entered = false;
    this->startTime = _startTime;
    this->duration = _duration;
    this->onEnter = _onEnter;
    this->update = _update;
    this->onExit = _onExit;
}
