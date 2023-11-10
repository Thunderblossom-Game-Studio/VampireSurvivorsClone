#include "Level.h"
#include "Core/DeltaTime.h"
#include "Rendering/RenderInstanceManager.h"

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


}

void Level::Render()
{
}

void Level::Clean()
{
}
