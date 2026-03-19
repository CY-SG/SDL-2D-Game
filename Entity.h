#pragma once
#include<vector>
#include<type_traits>
#include"Component.h"
#include<memory>
#include<string>
#include"SceneData.h"
class Entity {
public:
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value,
            "T must derive from Component");

        std::unique_ptr<T>comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->SetOwner(this);
        T* ptr = comp.get();
        components.push_back(std::move(comp));
        return ptr;
    }
    template<typename T>
    T* GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value,
            "T must derive from Component");

        for (int i = 0; i < components.size();i++) {
            Component* component = components[i].get();
            if (auto* p = dynamic_cast<T*>(component))
                return p;
        }
        return nullptr;
    }
    Entity(const std::string&name,Entity*parent = nullptr);
    Entity();
    Entity* GetChild(const std::string& name);
    Entity* GetParent(const std::string& name);
    void SetChild(std::unique_ptr<Entity>entity);
    void SetParent(Entity* entity);
    std::unique_ptr<Entity>Clone();
    bool needDestroy = false;
    std::vector<std::unique_ptr<Entity>>child;
    std::string name;
    int id = -1;
    ~Entity();
private:
    std::vector<std::unique_ptr<Component>>components;
};