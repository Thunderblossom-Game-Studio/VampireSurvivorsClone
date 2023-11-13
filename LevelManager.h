#pragma once
#include <map>
#include <string>

class Level;

class LevelManager
{
public:

	static void AddLevel(std::string id, Level* level);
	static void LoadLevel(std::string levelId);
	static void UnloadLevel(std::string levelId);
	static void UnloadActiveLevel();
	static Level* GetActiveLevel() { return _activeScene; }

	static void UpdateActiveLevel();

private:
	static std::map<std::string, Level*> _scenes;
	static Level* _activeScene;

};

