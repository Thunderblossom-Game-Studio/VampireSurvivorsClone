#pragma once

#include "../GameObjects/IRenderableObject.h"
#include "../GameObjects/BaseGameObject.h"
#include "../Core/Collider2D.h"
#include "../Core/Vector2.h"
#include <SDL.h>
#include <string>


class Tile : public BaseGameObject, public IRenderableObject
{
public:
	Tile(Vector2 position, Vector2 size, std::string texture_path, SDL_Rect src, int renderLayer, ColliderType collision);
	~Tile();

	float GetX() const override { return _position.x; }
	float GetY() const override { return _position.y; }

	float GetWidth() const override { return _tileSize.x; }
	float GetHeight() const override { return _tileSize.y; }

	void Collided(Collider2D& collider);
private:
	Vector2 _tileSize{ 0,0 };
	Collider2D* _collider{ nullptr };
	GameRenderer* _renderer{ nullptr };
};

