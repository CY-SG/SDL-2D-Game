#include "EngineTime.h"

void EngineTime::Init(Time* time)
{
    instance = time;
}

float EngineTime::deltaTime()
{
    return instance->DeltaTime();
}

void EngineTime::Tick()
{
    instance->Tick();
}

Time* EngineTime::instance = nullptr;