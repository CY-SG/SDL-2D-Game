#include "HpComponent.h"
#include"Entity.h"
#include"World.h"
void HpComponent::Update()
{
}

std::unique_ptr<Component> HpComponent::Clone(Entity* entity)
{
    std::unique_ptr<HpComponent>_clone = std::make_unique<HpComponent>(entity, this->maxHp);
    return std::move(_clone);
}

HpComponent::HpComponent(Entity* entity, int Hp)
{
    SetOwner(entity);
    this->maxHp = Hp;
    this->currHp = Hp;
}

void HpComponent::TakeDamage(int damage)
{
    this->currHp -= damage;
    if (this->currHp <= 0) {
        World::Instance()->DestroyEntity(owner);

    }
}
