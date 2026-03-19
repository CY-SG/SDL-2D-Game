#pragma once
class Entity;
class ControllerStrategy {
public:
	virtual void Update() = 0;
	ControllerStrategy();
	void SetEntity(Entity* entity);
protected:
	Entity* entity;
};