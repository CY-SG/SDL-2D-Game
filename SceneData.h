#pragma once
#include<unordered_map>
#include<string>
#include<functional>
#include<vector>
class Entity;
struct SceneCoord
{
    int x;
    int y;

    bool operator==(const SceneCoord& other) const
    {
        return x == other.x && y == other.y;
    }
};
struct SceneCoordHash
{
    size_t operator()(const SceneCoord& c) const
    {
        return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
    }
};

struct SpawnInfo
{
    int id;
    std::string prefabName;
    float x;
    float y;
    std::function<void(Entity*)> initializer;
};

struct SceneData
{
    std::vector<SpawnInfo> spawns;
};

struct SceneChunk
{
    SceneCoord coord;

    std::vector<int> spawnedEntities;
};

struct EntityState {
    bool IsDead = false;
    Entity* entity;
};