#include "LevelManager.h"
#include "Level.h"

std::map<std::string, Level*> LevelManager::_levels;
Level* LevelManager::_activeLevel;

void LevelManager::AddLevel(std::string id, Level* level)
{
	_levels[id] = level;
	_levels[id]->SetLevelId(id);
}

void LevelManager::LoadLevel(std::string levelId)
{
	UnloadActiveLevel();

	_activeLevel = _levels[levelId];

	_levels[levelId]->SetActive(true);

}

void LevelManager::UnloadActiveLevel()
{
	if(!_activeLevel)
		return;

	delete _activeLevel;
}

void LevelManager::UpdateActiveLevel()
{
	if (!_activeLevel)
		return;

	_activeLevel->Update();
}

void LevelManager::SpawnObject(BaseGameObject* gameObject)
{
	if(!_activeLevel)
		return;

	_activeLevel->SpawnInLevel(gameObject);
}
