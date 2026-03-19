#include "LifeTimeComponent.h"
#include "World.h"
#include "EngineTime.h"
LifeTimeComponent::LifeTimeComponent(Entity* entity, float _Lifetime):Lifetime(_Lifetime)
{
    SetOwner(entity);
}

void LifeTimeComponent::Update()
{
    curLifeTime += EngineTime::deltaTime();
    if (curLifeTime >= Lifetime) {
        World::Instance()->DestroyEntity(owner);
    }
}

std::unique_ptr<Component> LifeTimeComponent::Clone(Entity* entity)
{
    std::unique_ptr<LifeTimeComponent>_clone = std::make_unique<LifeTimeComponent>(entity, this->Lifetime);
    _clone.get()->curLifeTime = 0;
    return std::move(_clone);
}
