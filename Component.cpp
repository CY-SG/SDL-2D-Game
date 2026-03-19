#include "Component.h"
#include"Entity.h"
void Component::Update()
{
}

Entity* Component::GetOwner()
{
    return owner;
}

void Component::SetOwner(Entity* _owner)
{
    owner = _owner;
}
