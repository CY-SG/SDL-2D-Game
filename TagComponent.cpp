#include "TagComponent.h"

void TagComponent::Update()
{
}

std::unique_ptr<Component> TagComponent::Clone(Entity* entity)
{
    std::unique_ptr<TagComponent>_clone = std::make_unique<TagComponent>(entity, this->tag);
    return std::move(_clone);
}

TagComponent::TagComponent(Entity* entity, Tag tag)
{
    SetOwner(entity);
    this->tag = tag;
}
