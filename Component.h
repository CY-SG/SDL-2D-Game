#pragma once
#include"Math.h"
#include<memory>
class Entity;
class Component {
public:
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual std::unique_ptr<Component>Clone(Entity*entity) = 0;
	Entity* GetOwner();
	void SetOwner(Entity* _owner);
protected:
	Entity* owner;
};