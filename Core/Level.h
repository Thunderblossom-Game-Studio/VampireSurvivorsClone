#pragma once
#include <vector>
#include <string>

class BaseGameObject;
class TileMap;
class Player;

class Level
{
private:
	Player* _player;
	TileMap* _tileMap;
	std::vector<BaseGameObject*> _gameObjects;
	std::vector<BaseGameObject*> _runtimeObjects;
	std::vector<BaseGameObject*> _objectsToSpawn;
	std::string _levelId;
	bool _isActive;

	void DestroyMarkedForDestruction();

public:

	Level(const std::string& levelId, Player* player, TileMap* tileMap, std::vector<BaseGameObject*> gameObjects);
	~Level();

	void Update();

	void SpawnInLevel(BaseGameObject* gameObject);

#pragma region Getters/Setters
	std::string GetLevelId() { return _levelId; }
	void SetLevelId(std::string levelId) { _levelId = levelId; }

	bool IsActive() { return _isActive; }
	void SetActive(bool isActive) { _isActive = isActive; }

	std::vector<BaseGameObject*> GetGameObjects() { return _gameObjects; }
	Player* GetPlayer() { return _player; }

	BaseGameObject* FindObjectByTag(std::string id);

#pragma endregion

};

