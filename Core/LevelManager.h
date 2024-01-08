#pragma once
#include <map>
#include <string>

class Level;
class BaseGameObject;

class LevelManager
{
public:

	static void AddLevel(std::string id, Level* level);
	static void LoadLevel(std::string levelId);
	static void UnloadActiveLevel();
	static void UpdateActiveLevel();
	static Level* GetActiveLevel() { return _activeLevel; }

	static void SpawnObject(BaseGameObject* gameObject);

private:
	static std::map<std::string, Level*> _levels;
	static Level* _activeLevel;

};

