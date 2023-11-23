#include "Enemy.h"
#include "Player.h"
#include "../Core/Game.h"
#include "../Core/DeltaTime.h"
#include "../Core/CollisionManager.h"
#include "../Rendering/RenderInstanceManager.h"
#include <iostream>

Enemy::Enemy(float x, float y, float width, float height,
             float health, float speed,
             ColliderType shape,
             GameRenderer::RenderSpace renderSpace, SDL_Color color,
             BaseGameObject* target)
    : IAnimationObject("Assets/Textures/TextureLoadingTest.png", {
                                                           {129, 236, 15, 19},
                                                           {144, 236, 15, 19},
                                                           {161, 236, 15, 19},
                                                           {177, 236, 15, 19}
                                                       }, 2.0f, 1.0f)
{
    _width = width;
    _height = height;
    _renderSpace = renderSpace;
    _color = color;
    _position.x = x;
    _position.y = y;
    _speed = speed;
    _health = health;
    _player = target;

    switch (shape)
    {
    case ColliderType::RECTANGLE:
        {
            _collider = AddComponent<Collider2D>(new Collider2D(shape, {_width, _height}));
            _collider->SetOnCollisionCallback(std::bind(&Enemy::OnCollision, this, std::placeholders::_1));
            break;
        }
    case ColliderType::CIRCLE:
        {
            _collider = AddComponent<Collider2D>(new Collider2D(shape, {_width / 2}));
            _collider->SetOnCollisionCallback(std::bind(&Enemy::OnCollision, this, std::placeholders::_1));
            break;
        }
    }

    if (_collider)
        CollisionManager::RegisterCollider(_collider);

    SetTexture("Assets/Textures/TextureLoadingTest.png", {128, 236, 16, 19});
    GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
    renderer->AddToRenderList(this);
}

Enemy::~Enemy()
{
    GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
    renderer->RemoveFromRenderList(this);
}

void Enemy::Movement()
{
    // Track and move towards the player
    if (_player)
    {
        if (_player->GetX() > _position.x)
        {
            _position.x += DeltaTime::GetDeltaTime() * _speed;
            _flipped = false;
        }
        else if (_player->GetX() < _position.x)
        {
            _position.x -= DeltaTime::GetDeltaTime() * _speed;
            _flipped = true;
        }

        if (_player->GetY() > _position.y)
        {
            _position.y += DeltaTime::GetDeltaTime() * _speed;
        }
        else if (_player->GetY() < _position.y)
        {
            _position.y -= DeltaTime::GetDeltaTime() * _speed;
        }
    }
}

void Enemy::Attack()
{
    std::cout << "Enemy attacking" << std::endl;
}

void Enemy::OnDeath()
{
    std::cout << "Enemy died" << std::endl;

	_xpDrop = new XPPickUp(_position.x, _position.y, 10.f, 10.f, _player, ColliderType::RECTANGLE);
}

void Enemy::TakeDamage(float damage)
{
    _health -= damage;
}

void Enemy::OnCollision(Collider2D& other)
{
    if (other.GetGameObject() == _player)
    {
        auto dmg = dynamic_cast<IDamageable*>(other.GetGameObject());
        if (dmg)
        {
            // Damage the player
            dmg->TakeDamage(1.f);
        }
    }
}

void Enemy::Update(float deltaTime)
{
    Movement();
}

void Enemy::LateUpdate(float deltaTime)
{
    // Does nothing currently
}

RenderInfo Enemy::GetRenderInfo() const
{
    return RenderInfo(_position, {_width, _height}, _texture, _src, _flipped, _sortingLayer, _color);
}
