#pragma once
#include<vector>
#include<memory>
class Entity;
class Scene {
public:
	Scene();
	//void AddRootEntity(std::unique_ptr<Entity>entity);
	//void AddChildEntity(Entity* parent, std::unique_ptr<Entity>child);
	const std::vector<Entity*>& GetEntity()const;
	//void Update();
	//void RemoveEntity();
private:
	//void FlushAdd();
	//void HandleHierarchy();
	//void Traverse(Entity* root);
	//void RemoveChild(Entity* root);

	//½«ÒªÉ¾³ýµÄ
	//std::vector<std::unique_ptr<Entity>>roots;
	//std::vector<std::pair<Entity*,std::unique_ptr<Entity>>>toAddentities;
	//std::vector<Entity*>entities;



};
