#include "DamageComponent.h"
#include"EngineTime.h"
void DamageComponent::Update()
{
    currTime += EngineTime::deltaTime();
    if (currTime >= duration) {
        currTime = 0.0f;
        attackTarget.clear();
    }
}

std::unique_ptr<Component> DamageComponent::Clone(Entity* entity)
{
    std::unique_ptr<DamageComponent>_clone = std::make_unique<DamageComponent>(entity, this->damage, this->duration);
    return std::move(_clone);
}

DamageComponent::DamageComponent(Entity* entity, int damage, float duration)
{
    SetOwner(entity);
    this->damage = damage;
    this->duration = duration;
    currTime = 0.0f;
}
