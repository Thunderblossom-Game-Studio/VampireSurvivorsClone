#pragma once

#include "BaseGameObject.h"
#include "ExampleGameObject.h"
#include "Player.h"

class EnemySpawner final : public BaseGameObject
{

private:
    float _spawnerRadius = 0;
    float _spawnRate = 0;
    float _spawnTimer = 0;
    BaseGameObject* _objectSpawnReference;
    
public:
    Vector2 GetRandomPointInCircle(Vector2 circlePosition) const;
    void SpawnObject() const;
    EnemySpawner(BaseGameObject* objectSpawnReference, float spawnerRadius, float spawnRate);
    ~EnemySpawner() override;
};

