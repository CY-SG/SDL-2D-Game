#include "Entity.h"
#include"TransformComponent.h"
#include"CoroutineManager.h"
Entity::Entity(const std::string& name, Entity* parent)
{
	this->name = name;
	AddComponent<TransformComponent>(this,parent);
}

Entity::Entity()
{
}

Entity* Entity::GetChild(const std::string& name)
{
	if (this->name == name)return this;
	Entity* result = nullptr;
	for (auto& t : child) {
		result = t.get()->GetChild(name);
		if (result != nullptr)return result;
	}
	return nullptr;
}

Entity* Entity::GetParent(const std::string& name)
{
	if (this->name == name)return this;
	Entity* parent = GetComponent<TransformComponent>()->parent->GetOwner();
	if (parent == nullptr)return nullptr;
	Entity* result = parent->GetParent(name);
	return result;
}

void Entity::SetChild(std::unique_ptr<Entity> entity)
{
	TransformComponent* childTransformComponent = entity.get()->GetComponent<TransformComponent>();
	TransformComponent* transformComponent = this->GetComponent<TransformComponent>();
	childTransformComponent->parent = transformComponent;
	child.push_back(std::move(entity));
}

void Entity::SetParent(Entity* entity)
{
}

std::unique_ptr<Entity> Entity::Clone()
{
	Entity* _clone = new Entity();
	_clone->name = this->name;
	for (int i = 0; i < components.size(); i++) {
		_clone->components.push_back(std::move(components[i].get()->Clone(_clone)));
	}
	_clone->needDestroy = false;
	TransformComponent* _cloneComponent = _clone->GetComponent<TransformComponent>();
	for (auto& t : child) {
		std::unique_ptr<Entity>_child = std::move(t.get()->Clone());
		TransformComponent* childComponent = _child.get()->GetComponent<TransformComponent>();
		_cloneComponent->child.push_back(childComponent);
		childComponent->parent = _cloneComponent;
		_clone->child.push_back(std::move(_child));
	}
	return std::move(std::unique_ptr<Entity>(_clone));
}

Entity::~Entity()
{
	CoroutineManager::Instance()->CancelCoroutineByEntity(this);
}
