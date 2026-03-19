#include "Scene.h"
#include"World.h"
#include"System.h"
#include"Entity.h"
#include"TransformComponent.h"
Scene::Scene()
{
}

//void Scene::AddRootEntity(std::unique_ptr<Entity> entity)
//{
//    toAddentities.push_back({ nullptr,std::move(entity) });
//}
//
//void Scene::AddChildEntity(Entity* parent, std::unique_ptr<Entity> child)
//{
//    toAddentities.push_back({ parent,std::move(child) });
//}
//
//const std::vector<Entity*>& Scene::GetEntity()const
//{
//	return entities;
//}
//
//void Scene::Update()
//{
//    HandleHierarchy();
//	auto& t = World::Instance()->GetSystems();
//	for (auto& p : t) {
//		p.get()->Update();
//	}
//    RemoveEntity();
//    FlushAdd();
//}

//void Scene::RemoveEntity()
//{
//    //清理root
//    roots.erase(
//        std::remove_if(
//            roots.begin(),
//            roots.end(),
//            [](const std::unique_ptr<Entity>& e)
//            {
//                return e.get()->needDestroy == true;
//            }),
//        roots.end());
//    //清理child
//    for (auto& t : roots)RemoveChild(t.get());
//}
//
//void Scene::FlushAdd()
//{
//    for (auto& t : toAddentities) {
//        if (t.first == nullptr) {
//            t.second.get()->GetComponent<TransformComponent>()->parent = nullptr;
//            roots.push_back(std::move(t.second));
//        }
//        else {
//            TransformComponent* parentComponent = t.first->GetComponent<TransformComponent>();
//            TransformComponent* childComponent = t.second.get()->GetComponent<TransformComponent>();
//            parentComponent->child.push_back(childComponent);
//            childComponent->parent = parentComponent;
//
//            t.first->child.push_back(std::move(t.second));
//        }
//    }
//    toAddentities.clear();
//}
//
//void Scene::HandleHierarchy()
//{
//    entities.clear();
//    for (auto& t : roots) {
//        Traverse(t.get());
//    }
//}
//
//void Scene::Traverse(Entity* root)
//{
//    entities.push_back(root);
//    for (auto& t : root->child) {
//        Traverse(t.get());
//    }
//}
//
//void Scene::RemoveChild(Entity* root)
//{
//    root->child.erase(
//        std::remove_if(
//            root->child.begin(),
//            root->child.end(),
//            [](const std::unique_ptr<Entity>& e)
//            {
//                return e.get()->needDestroy == true;
//            }),
//        root->child.end());
//    for (auto& t : root->child)RemoveChild(t.get());
//}
