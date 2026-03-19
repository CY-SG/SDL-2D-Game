#include "CoroutineManager.h"
#include"EngineTime.h"
#include<iostream>
int CoroutineManager::nextiD = 0;
CoroutineManager* CoroutineManager::instance = nullptr;

void CoroutineManager::Update()
{
    RemoveCoroutineByEntity();
    float dt = EngineTime::deltaTime();
    for (auto& t : coroutines) {
        t.currTime += dt;
        t.Update();
    }
}

int CoroutineManager::StartCoroutine(Entity* entity, const std::string& group, std::vector<CoroutineStep> timeline)
{
    Coroutine coroutine(entity, nextiD, group, timeline);
    for (auto& c : coroutines)
    {
        if (c.owner == entity && c.group == group && !c.IsFinish)
        {
            return -1;// 已存在，不再创建
        }
    }
    coroutines.push_back(coroutine);
    return nextiD++;
}

void CoroutineManager::CancelCoroutineByEntity(Entity* entity)
{
    for (auto& t : coroutines) {
        if (t.owner == entity)t.IsFinish = true;
    }
}

void CoroutineManager::CancelCoroutineById(int id)
{
    for (auto& t : coroutines) {
        if (t.id == id)t.IsFinish = true;
    }
}

void CoroutineManager::CancelCoroutineByGroup(Entity* entity, const std::string& name)
{
    for (auto& t : coroutines) {
        if (t.owner == entity && t.group == name)t.IsFinish = true;
    }
}

CoroutineManager* CoroutineManager::Instance()
{
    if (!instance)instance = new CoroutineManager();
    return instance;
}

CoroutineManager::CoroutineManager()
{
}

void CoroutineManager::RemoveCoroutineByEntity()
{
    coroutines.erase(
        std::remove_if(
            coroutines.begin(),
            coroutines.end(),
            [](const Coroutine& e)
            {
                return e.IsFinish == true;
            }),
        coroutines.end());
}
