#include "EnemySpawner.h"

#include "Enemy.h"

EnemySpawner::~EnemySpawner() = default;

void EnemySpawner::Update(float deltaTime)
{
    _spawnTimer += deltaTime;
    if (_spawnTimer >= _spawnRate)
    {
        SpawnEnemy();
        _spawnTimer = 0;
    }
}

EnemySpawner::EnemySpawner(BaseGameObject* objectSpawnReference, float spawnerRadius, float spawnRate)
{
    _objectSpawnReference = objectSpawnReference;
    _spawnerRadius = spawnerRadius;
    _spawnRate = spawnRate;
}

Vector2 EnemySpawner::GetRandomPointInCircle(Vector2 circlePosition) const
{
    const float randomAngle = rand() % 360;
    const Vector2 randomPointInCircle = {
        circlePosition.x + _spawnerRadius * cos(randomAngle),
        circlePosition.y + _spawnerRadius * sin(randomAngle) };
    return randomPointInCircle;
}

Vector2 EnemySpawner::GetSpawnPosition() const
{
    const Vector2 spawnReferencePosition = Vector2(_objectSpawnReference->GetX(), _objectSpawnReference->GetY());
    return GetRandomPointInCircle(spawnReferencePosition);
}

void EnemySpawner::SpawnEnemy()
{
    const Vector2 spawnPosition = GetSpawnPosition();
    
    Enemy* enemy = new Enemy
    (spawnPosition.x, spawnPosition.y, 50, 50, 10, 100,
        ColliderType::CIRCLE, GameRenderer::RenderSpace::WORLD,
        { 255,255,255,255 }, _objectSpawnReference);

    _currentEnemies.push_back(enemy);
    std::cout << "Spawned enemy at: " << enemy->GetX() << ", " << enemy->GetY() << std::endl;

    //not sure how to integrate this into the level system, but this method would be called on a set tick with a position
    //whoever designed the level system should be able to figure out how to integrate this into the level system
}

void EnemySpawner::Clean()
{
    for (const auto& enemy : _currentEnemies)
        delete enemy;
    
    _currentEnemies.clear();
}


