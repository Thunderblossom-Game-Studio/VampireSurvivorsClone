#pragma once

#include "BaseGameObject.h"
#include "ExampleGameObject.h"
#include "Player.h"
class EnemySpawner : public BaseGameObject
{

private:
    float _spawnerRadius = 0.0f;
    BaseGameObject* _objectSpawnReference;
    float _spawnRate = 5.0f;
    float _spawnTimer = 0.0f;
    std::vector<class Enemy*> _currentEnemies;
    
public:
    Vector2 GetRandomPointInCircle(Vector2 circlePosition) const;
    Vector2 GetSpawnPosition() const;
    void SpawnEnemy();
    void Clean();
    void Update(float deltaTime) override;
   // void LateUpdate(float deltaTime) override;
    
    EnemySpawner(BaseGameObject* objectSpawnReference, float spawnerRadius, float spawnRate);
    ~EnemySpawner() override;
};

