#pragma once
#include "BaseGameObject.h"
#include "IAnimationObject.h"
#include "../Core/CollisionManager.h"
#include "../Components/Collider2D.h"
//#include "../GameObjects/IDamageable.h"

class Enemy final : public BaseGameObject, public IAnimationObject
{
private:
	Collider2D* _collider = nullptr;
public:
	float _width = 0;
	float _height = 0;
	float _enemyHP = 0;
	float _enemyMovementSpeed = 0;

	Enemy(float x, float y, float width, float height,
		float enemyHP, float enemyMovementSpeed, ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~Enemy();

	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }

	void EnemyMovement();
	void EnemyAttack();

	void UpdateEnemy(); //Updates every tick.
	void OnDeath(); //Events when the enemy dies.

	RenderInfo GetRenderInfo() const override;
};
