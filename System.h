#pragma once
class EntityManager;
class Scene;
class Entity;
class System {
public:
	virtual ~System() = default;
	virtual void Update() = 0;
private:
};