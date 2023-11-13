#pragma once
#include <vector>
#include <string>
#include "GameObjects/Player.h"
#include "Core/CollisionManager.h"

class BaseGameObject;
class TileMap;

class Level
{

private:
	Player* _player;
	TileMap* _tileMap;
	
	std::vector<BaseGameObject*> gameObjects;

	std::string _levelId;
	bool _isActive;

public:

	Level(const std::string& levelId, Player* player, TileMap* tileMap);
	~Level();

	void Update();
	void Render();
	void Clean();

#pragma region Getters/Setters
	std::string GetLevelId() { return _levelId; }
	void SetLevelId(std::string levelId) { _levelId = levelId; }

	bool IsActive() { return _isActive; }
#pragma endregion

};

