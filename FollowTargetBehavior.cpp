#include "FollowTargetBehavior.h"
#include"Entity.h"
#include"EngineTime.h"
#include"TransformComponent.h"
#include"Camera2D.h"
FollowTargetBehavior::FollowTargetBehavior(Entity* entity, float t)
{
    SetEntity(entity);
    SetLerpSpeed(t);
}

void FollowTargetBehavior::SetEntity(Entity* entity)
{
    this->entity = entity;
}

void FollowTargetBehavior::SetLerpSpeed(float t)
{
    lerpSpeed = t;
}

void FollowTargetBehavior::Update(Camera2D* camera)
{
    Vec2 pos = entity->GetComponent<TransformComponent>()->pos;
    Vec2 from = camera->GetPos();
    Vec2 screenSize = camera->GetScreenSize();
    float to_x = pos.x - screenSize.x / 2.0f;
    float to_y = pos.y - screenSize.y / 2.0f;
    Vec2 target = Lerp(from, Vec2(to_x, to_y), lerpSpeed);
    camera->SetPos(target.x, target.y);
}

Vec2 FollowTargetBehavior::Lerp(const Vec2& from, const Vec2& to, float t)
{
    return from + (to - from) * t;
}
