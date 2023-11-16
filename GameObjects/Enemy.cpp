#include "Enemy.h"
#include "Player.h"
#include "../Core/Game.h"
#include "../GameObjects/BaseGameObject.h"
#include "../Core/DeltaTime.h"
#include "../Rendering/RenderInstanceManager.h"
#include <iostream>

Enemy::Enemy(float x, float y, float width, float height,
	float enemyHP, float enemyMovementSpeed, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color) : _width(width), _height(height), IAnimationObject("Assets/Textures/TextureLoadingTest.png", { { 129, 236, 15, 19 },
																									{ 144, 236, 15, 19 },
																									{ 161, 236, 15, 19 },
																									{ 177, 236, 15, 19 } }, 2.0f, 1.0f)
{

	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;
	_enemyHP = enemyHP;
	_enemyMovementSpeed = enemyMovementSpeed;

	switch (shape)
	{
	case ColliderType::RECTANGLE:
	{
		_collider = AddComponent<Collider2D>(new Collider2D(shape, { _width, _height }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	case ColliderType::CIRCLE:
	{
		_collider = AddComponent<Collider2D>(new Collider2D(shape, { _width / 2 }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	}

	if (_collider)
		CollisionManager::RegisterCollider(_collider);

	SetTexture("Assets/Textures/TextureLoadingTest.png", { 128,236,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);
	EnemyMovement();
}

Enemy::~Enemy()
{
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->RemoveFromRenderList(this);
}

void Enemy::EnemyMovement()
{
	
}

void Enemy::EnemyAttack()
{
	std::cout << "Attack" << std::endl;
}

void Enemy::OnDeath()
{
	/*Score change, level change, any event goes here.*/
}

void Enemy::UpdateEnemy()
{
	// /*Checks if enemy is dead...*/
	//if (GetHealth() < 1)
	//{
	//	OnDeath();
	//}
}

RenderInfo Enemy::GetRenderInfo() const
{
	return RenderInfo(_position, { _width, _height }, _texture, _src, _flipped, _sortingLayer, _color);
}