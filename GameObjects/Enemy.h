#pragma once
#include "BaseGameObject.h"
#include "IAnimationObject.h"
#include "../Components/Collider2D.h"
#include "../Gameplay/XPPickUp.h"
#include "../GameObjects/IDamageable.h"

class Enemy : public BaseGameObject, public IAnimationObject, public IDamageable
{
private:
	Collider2D* _collider = nullptr;
	float _width = 0;
	float _height = 0;
	float _speed = 0;

	// Player target
	BaseGameObject* _player = nullptr;
	
public:

	Enemy(float x, float y, float width, float height,
		float health, float speed,
		ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace renderSpace = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 },
		BaseGameObject* target = nullptr);
	
	~Enemy();

	// Position
	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	// Scale
	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }

	// Actions
	void Movement();
	void Attack();

	// Default functions
	void Update(float deltaTime) override; //Updates every tick.
	void LateUpdate(float deltaTime) override; //Updates every tick after Update.
	void OnDeath(); //Events when the enemy dies.

	void TakeDamage(float damage) override;

	// Collision
	void OnCollision(Collider2D& other);

	XPPickUp* _xpDrop;

	RenderInfo GetRenderInfo() const override;
};
