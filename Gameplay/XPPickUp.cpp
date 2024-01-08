#include "XPPickUp.h"

#include "../Rendering/RenderInstanceManager.h"

XPPickUp::XPPickUp(float x, float y, float width, float height, BaseGameObject* target, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color) : IAnimationObject("Assets/Textures/TextureLoadingTest.png", { { 129, 45, 15, 19 },
	                                                                                                                                                                                 { 144, 45, 15, 19 },{ 161, 45, 15, 19 },{ 177, 45, 15, 19 } }, 2.0f, 1.0f) 
{

	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;
	_target = target;

	

	switch (shape)
	{
	case ColliderType::RECTANGLE:
	{
		_collider = AddComponent<Collider2D>(new Collider2D(shape, { width, height }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	case ColliderType::CIRCLE:
	{
		//_collider = new Collider2D(shape, _width / 2);

		_collider = AddComponent<Collider2D>(new Collider2D(shape, { width / 2 }));
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	}

	if (_collider)
	{
		CollisionManager::RegisterCollider(_collider);
	}

	SetTexture("Assets/Textures/TextureLoadingTest.png", { 144,45,15,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);
}

void XPPickUp::OnCollision(Collider2D& other)
{
	if(other.GetGameObject() == _target)
	{
		delete this;
	}
}







XPPickUp::~XPPickUp()
{
	if (_collider)
	{
		delete _collider;
	}
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->RemoveFromRenderList(this);
}

RenderInfo XPPickUp::GetRenderInfo() const
{
		return RenderInfo(_position, { _width, _height }, _texture, _src, _flipped, _sortingLayer, _color);
}

void XPPickUp::Update(float deltaTime)
{
}

void XPPickUp::LateUpdate(float deltaTime)
{
}

