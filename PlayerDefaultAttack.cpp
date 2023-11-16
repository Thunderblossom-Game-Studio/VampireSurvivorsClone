#include "PlayerDefaultAttack.h"
//#include "GameObjects/Player.h"
#include "Rendering/RenderInstanceManager.h"
#include <iostream>

#include "Core/DeltaTime.h"

PlayerDefaultAttack::PlayerDefaultAttack(float x, float y, float width, float height, float attackDamage, float attackTillAttack,bool flip, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color)
{
	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;
	_width = width;
	_height = height;
	AttackTimer = attackTillAttack;
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

	SetTexture("Assets/Textures/TextureLoadingTest.png", { 180,45,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);

}

PlayerDefaultAttack::~PlayerDefaultAttack()
{
	if (_collider)
	{
		delete _collider;
	}
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->RemoveFromRenderList(this);
}

bool PlayerDefaultAttack::Attack()
{
	//TimeKeep = true;

		if(_collider)
		{
			_collider->SetPosition(_position);
		}
	
		TimeToReset += DeltaTime::GetDeltaTime();

		if (TimeToReset >= AttackTimer)
		{
			std::cout << "Attack Out" << std::endl;
			//PlayerDefaultAttack::~PlayerDefaultAttack();
			//delete this;
			TimeToReset = 0;
			return true;
			//TimeKeep = false;

		}

	return false;
}

RenderInfo PlayerDefaultAttack::GetRenderInfo() const
{
	return RenderInfo(_position, { _width, _height }, _texture, _src, _flipped, _sortingLayer, _color);
}