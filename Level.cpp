#include "Level.h"
#include "Core/DeltaTime.h"
#include "Rendering/RenderInstanceManager.h"
#include "Core/CollisionManager.h"

Level::Level(const std::string& levelId, Player* player, TileMap* tileMap)
{
	_levelId = levelId;
	_player = player;
	_tileMap = tileMap;


	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->SetObjectToTrack(_player);  
}

void Level::Update()
{
	DeltaTime::UpdateDeltaTime();

	CollisionManager::HandleCollisions();


	// Updates input state and performs any bound callbacks
	InputManager::instance().Update();

	// Game Objects parsed into Draw function, all 'IRenderableObject' objects will be rendered to that renderer - rest ignored.
	RenderInstanceManager::instance().GetRenderer("main")->Draw();

}

void Level::Render()
{
}

void Level::Clean()
{
}
