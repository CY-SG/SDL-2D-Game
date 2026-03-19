#include "AISensorController.h"
#include"Entity.h"
#include"TransformComponent.h"
#include"AIControllerComponent.h"
AISensorController::AISensorController(Entity* entity):ControllerComponent(entity)
{
}

void AISensorController::Update()
{
    Entity* parent = owner->GetComponent<TransformComponent>()->parent->GetOwner();
    AIControllerComponent* aiControllerComponent = parent->GetComponent<AIControllerComponent>();
    TransformComponent* transformComponent = owner->GetComponent<TransformComponent>();
    transformComponent->pos.x = abs(transformComponent->pos.x) * (aiControllerComponent->faceleft == true ? -1 : 1);
}

std::unique_ptr<Component> AISensorController::Clone(Entity* entity)
{
    std::unique_ptr<AISensorController>_clone = std::make_unique<AISensorController>(entity);
    return std::move(_clone);
}
