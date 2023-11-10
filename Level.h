#pragma once
#include <vector>
#include <string>

class Player;
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


	void Init();
	void Update();
	void Render();
	void Clean();

};

