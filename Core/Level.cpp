#include "Level.h"
#include "../Core/DeltaTime.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../Rendering/Renderer.h"
#include "../GameObjects/BaseGameObject.h"
#include "../Rendering/TileMap.h"
#include "../GameObjects/Player.h"

Level::Level(const std::string& levelId, Player* player, TileMap* tileMap, std::vector<BaseGameObject*> gameObjects)
{
	_levelId = levelId;
	_player = player;
	_tileMap = tileMap;
	_gameObjects = gameObjects;

	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->SetObjectToTrack(_player);  
}

Level::~Level()
{
	delete _player;

	delete _tileMap;

	for (auto& gameObject : _gameObjects)
		delete gameObject;

	_gameObjects.clear();
}

void Level::Update()
{
	CollisionManager::HandleCollisions();

	_player->Update(DeltaTime::GetDeltaTime());

	for (auto& GameObject : _gameObjects)
	{
		GameObject->Update(DeltaTime::GetDeltaTime());
	}

	for (auto& gameObject : _runtimeObjects)
	{
		_objectsToSpawn.push_back(gameObject);
	}

	_gameObjects.insert(_gameObjects.end(), _objectsToSpawn.begin(), _objectsToSpawn.end());

	_objectsToSpawn.clear();
	_runtimeObjects.clear();

	// Updates input state and performs any bound callbacks
	InputManager::instance().Update();

	// Game Objects parsed into Draw function, all 'IRenderableObject' objects will be rendered to that renderer - rest ignored.
	RenderInstanceManager::instance().GetRenderer("main")->Draw();

	DestroyMarkedForDestruction();
}

void Level::SpawnInLevel(BaseGameObject* gameObject)
{


}

void Level::DestroyMarkedForDestruction()
{
	if(_player->IsMarkedForDestruction())
	{
		delete _player;
		CollisionManager::UnregisterCollider(_player->GetComponent<Collider2D>());
		_player = nullptr;
	}

	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->IsMarkedForDestruction())
		{
			delete gameObject;
			CollisionManager::UnregisterCollider(gameObject->GetComponent<Collider2D>());
			gameObject = nullptr;
		}
	}
	_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), nullptr), _gameObjects.end());
}

BaseGameObject* Level::FindObjectByTag(std::string tag)
{
	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetTag() == tag)
		{
			return gameObject;
		}
	}

	return nullptr;
}
