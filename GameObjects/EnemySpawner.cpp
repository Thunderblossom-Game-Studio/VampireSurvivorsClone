#include "EnemySpawner.h"

EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(BaseGameObject* objectSpawnReference, float spawnerRadius, float spawnRate)
{
    _objectSpawnReference = objectSpawnReference;
    _spawnerRadius = spawnerRadius;
    _spawnTimer = spawnRate;
}

Vector2 EnemySpawner::GetRandomPointInCircle(Vector2 circlePosition) const
{
    const float randomAngle = rand() % 360;
    const Vector2 randomPointInCircle = {
        circlePosition.x + _spawnerRadius * cos(randomAngle),
        circlePosition.y + _spawnerRadius * sin(randomAngle) };
    return randomPointInCircle;
}

void EnemySpawner::SpawnObject() const
{
    const Vector2 spawnReferencePosition = Vector2(_objectSpawnReference->GetX(), _objectSpawnReference->GetY());
    Vector2 randomPointInCircle = GetRandomPointInCircle(spawnReferencePosition);

    //Replace With Spawning Object, want to discuss with everyone how exactly they want to handle this, prefabs or something else?
    std::cout << randomPointInCircle;
}
