#include "World.h"
#include"SceneManager.h"
#include"PrefabManager.h"
#include"Entity.h"
#include"CameraSystem.h"
#include"RenderSystem.h"
#include"AnimationSystem.h"
#include"PhysicsSystem.h"
#include"ControllerSystem.h"
#include"InputSystem.h"
#include"LifeTimeSystem.h"
#include"DebugSystem.h"
#include"DamageSystem.h"
#include"TransformComponent.h"
#include"TransformSystem.h"
#include"CoroutineManager.h"
World* World::instance = nullptr;
World* World::Instance()
{
    if (instance == nullptr) {
        instance = new World();
    }
    return instance;
}

void World::Update()
{
    this->renderer.get()->BeginFrame();
    this->renderer.get()->Clear();

    sceneManager.get()->UpdateStreaming();
    cameraSystem.get()->Update();
    WorldUpdate();
    CoroutineManager::Instance()->Update();

    this->renderer.get()->EndFrame();
}

PrefabManager* World::GetPrefabManager()
{
    return prefabManager.get();
}

SceneManager* World::GetSceneManager()
{
    return sceneManager.get();
}

void World::Initial(std::unique_ptr<Render>renderer, std::unique_ptr<Camera2D>camera2D, std::unique_ptr<ResourceManager> resourceManager, std::unique_ptr<AnimationClipManager> animationClipManager)
{
    this->renderer = std::move(renderer);
    this->camera2D = std::move(camera2D);
    this->resourceManager = std::move(resourceManager);
    this->animationClipManager = std::move(animationClipManager);
    prefabManager = std::make_unique<PrefabManager>();
    prefabManager.get()->Initial(this->resourceManager.get(), this->animationClipManager.get());

    cameraSystem = std::make_unique<CameraSystem>(this->camera2D.get());
    systems.push_back(std::make_unique<InputSystem>());
    systems.push_back(std::make_unique<ControllerSystem>());
    systems.push_back(std::make_unique<DamageSystem>());
    systems.push_back(std::make_unique<PhysicsSystem>());
    systems.push_back(std::make_unique<TransformSystem>());
    systems.push_back(std::make_unique<AnimationSystem>());
    systems.push_back(std::make_unique<RenderSystem>(this->renderer.get(), this->camera2D.get()));
    systems.push_back(std::make_unique<LifeTimeSystem>());
    systems.push_back(std::make_unique<DebugSystem>(this->renderer.get(), this->camera2D.get()));

    sceneManager = std::make_unique<SceneManager>();
    sceneManager.get()->InitLoad(persitentCoord);
}

const std::vector<std::unique_ptr<System>>& World::GetSystems() const
{
    return systems;
}

CameraSystem* World::GetCameraSystem() const
{
    return cameraSystem.get();
}

void World::RemoveEntity()
{
    //清理root
    roots.erase(
        std::remove_if(
            roots.begin(),
            roots.end(),
            [](const std::unique_ptr<Entity>& e)
            {
                return e.get()->needDestroy == true;
            }),
        roots.end());
    //清理child
    for (auto& t : roots)RemoveChild(t.get());
}

void World::AddRootEntity(std::unique_ptr<Entity> entity)
{
    toAddentities.push_back({ nullptr,std::move(entity) });
}

void World::AddChildEntity(Entity* parent, std::unique_ptr<Entity> child)
{
    toAddentities.push_back({ parent,std::move(child) });
}

void World::FlushAdd()
{
    for (auto& t : toAddentities) {
        if (t.first == nullptr) {
            t.second.get()->GetComponent<TransformComponent>()->parent = nullptr;
            roots.push_back(std::move(t.second));
        }
        else {
            TransformComponent* parentComponent = t.first->GetComponent<TransformComponent>();
            TransformComponent* childComponent = t.second.get()->GetComponent<TransformComponent>();
            parentComponent->child.push_back(childComponent);
            childComponent->parent = parentComponent;

            t.first->child.push_back(std::move(t.second));
        }
    }
    toAddentities.clear();
}

void World::HandleHierarchy()
{
    entities.clear();
    for (auto& t : roots) {
        Traverse(t.get());
    }
}

void World::Traverse(Entity* root)
{
    entities.push_back(root);
    for (auto& t : root->child) {
        Traverse(t.get());
    }
}

void World::RemoveChild(Entity* root)
{
    auto& children = root->child;

    children.erase(
        std::remove_if(
            children.begin(),
            children.end(),
            [](const std::unique_ptr<Entity>& e)
            {
                return e->needDestroy;
            }),
        children.end()
    );
    for (auto& c : children)
    {
        RemoveChild(c.get());
    }
}

void World::WorldUpdate()
{
    HandleHierarchy();
    auto& t = World::Instance()->GetSystems();
    for (auto& p : t) {
        p.get()->Update();
    }
    RemoveEntity();
    FlushAdd();
}


Entity* World::Instantiate(const std::string& name)
{
    std::unique_ptr<Entity>entity = std::move(prefabManager.get()->GetPrefab(name));
    Entity* temp = entity.get();
    AddRootEntity(std::move(entity));
    return temp;
}

Entity* World::Instantiate(const std::string& name, Entity* parent)
{
    std::unique_ptr<Entity>entity = std::move(prefabManager.get()->GetPrefab(name));
    Entity* temp = entity.get();
    AddChildEntity(parent, std::move(entity));
    return temp;
}

void World::DestroyEntityByScene(Entity* entity)
{
    entity->needDestroy = true;
}

void World::DestroyEntity(Entity* entity)
{
    if (entity->id != -1) {
        sceneState[entity->id].IsDead = true;
    }
    //TransformComponent* transformComponent = entity->GetComponent<TransformComponent>();
    entity->needDestroy = true;
 /*   for (auto& t : transformComponent->child) {
        DestroyEntity(t->GetOwner());
    }*/
}
