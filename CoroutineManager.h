#pragma once
#include"Coroutine.h";
class CoroutineManager {
public:
	void Update();
	int StartCoroutine(Entity* entity, const std::string& group, std::vector<CoroutineStep> timeline);
	void CancelCoroutineByEntity(Entity* entity);
	void CancelCoroutineById(int id);
	void CancelCoroutineByGroup(Entity* entity, const std::string& name);
	static CoroutineManager* Instance();
private:
	CoroutineManager();
	void RemoveCoroutineByEntity();
	static int nextiD;
	static CoroutineManager* instance;
	std::vector<Coroutine>coroutines;
};