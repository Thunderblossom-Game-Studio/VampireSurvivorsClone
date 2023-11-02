#include "Tile.h"
#include "../Core/AssetManager.h"
#include "../Core/CollisionManager.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../GameObjects/Player.h"

Tile::Tile(Vector2 position, Vector2 size, std::string texture_path, SDL_Rect src, int renderLayer, ColliderType collision)
{
	_position = position;
	_tileSize = size;
	SetTexture(texture_path, src);
	SetSortingLayer(renderLayer);
	
	_renderer = RenderInstanceManager::instance().GetRenderer("main");
	if (_renderer)
		_renderer->AddToRenderList(this);

	if (collision == ColliderType::NONE)
		return;
	_collider = new Collider2D(collision, _tileSize);
	_collider->SetPosition(_position);
	_collider->SetGameObject(this);
	_collider->SetOnCollisionCallback(std::bind(&Tile::Collided, this, std::placeholders::_1));
	CollisionManager::RegisterCollider(_collider);
}

Tile::~Tile()
{
}

void Tile::Collided(Collider2D& collider)
{
}
