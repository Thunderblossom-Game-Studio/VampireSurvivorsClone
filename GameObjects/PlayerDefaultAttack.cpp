#include "PlayerDefaultAttack.h"
#include "../Rendering/RenderInstanceManager.h"
#include <iostream>

#include "../Core/DeltaTime.h"

PlayerDefaultAttack::PlayerDefaultAttack(float x, float y, float width, float height, float attackDamage, float attackTillAttack,bool flip, BaseGameObject* target, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color)
{
	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;
	_width = width;
	_height = height;
	_attackDamage = attackDamage;
	_attackTimer = attackTillAttack;
	TimeKeep = 0;
	TimeToReset = 0;
	_target = target;
	//_target = target;
	Flip(flip);

	switch(shape)
	{
	case ColliderType::RECTANGLE:
	{
		//_collider = new Collider2D(shape, { _width, _height });

		_collider = AddComponent<Collider2D>(new Collider2D(shape, { _width, _height }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	case ColliderType::CIRCLE:
	{
		//_collider = new Collider2D(shape, _width / 2);

		_collider = AddComponent<Collider2D>(new Collider2D(shape, { _width / 2 }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	}

	if (_collider)
		CollisionManager::RegisterCollider(_collider);

	std::cout << "Spawn Attack" << std::endl;
	SetTexture("Assets/Textures/TextureLoadingTest.png", { 290,15,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);

}

PlayerDefaultAttack::~PlayerDefaultAttack()
{
	SetTexture("Assets/Textures/TextureLoadingTest.png", { 0,0,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->RemoveFromRenderList(this);	
	
	if (_collider)
	{
		CollisionManager::UnregisterCollider(_collider);
		delete _collider;
	}
	
}

bool PlayerDefaultAttack::Attack()
{
	//TimeKeep = true;

		if(_collider)
		{
			_collider->SetPosition(_position);
		}
	
		//TimeToReset += DeltaTime::GetDeltaTime();

	//	if (TimeToReset >= _attackTimer)
		//{
			//std::cout << "Attack Out" << std::endl;
			//PlayerDefaultAttack::~PlayerDefaultAttack();
			//delete this;
		//	TimeToReset = 0;
			return true;
			//TimeKeep = false;

	//	}

	//return false;
}

void PlayerDefaultAttack::Update(float deltatime)
{

}

void PlayerDefaultAttack::LateUpdate(float deltatime)
{

}

void PlayerDefaultAttack::OnCollision(Collider2D& other)
{
	if(other.GetGameObject() != _target) //needs to check for enemy
	{
		auto otherTarget = dynamic_cast<IDamageable*>(other.GetGameObject());
		if (otherTarget)
		{
			// Damage the enemy
			otherTarget->TakeDamage(_attackDamage);
		}
	}

}

RenderInfo PlayerDefaultAttack::GetRenderInfo() const
{
	return RenderInfo(_position, { _width, _height }, _texture, _src, _flipped, _sortingLayer, _color);
}

