#include "BasePickUp.h"

BasePickUp::BasePickUp(float x, float y, float width, float height, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color) : IAnimationObject("Assets/Textures/TextureLoadingTest.png", { { 129, 45, 15, 19 },
																																							{ 144, 45, 15, 19 },
																																							{ 161, 45, 15, 19 },																																							{ 177, 45, 15, 19 } }, 2.0f, 1.0f)
{
	switch (shape)
	{
	case ColliderType::RECTANGLE:
	{
		_collider = AddComponent<Collider2D>(new Collider2D(shape, { width, height }));
		_collider->SetOnCollisionCallback(std::bind(&BasePickUp::OnCollisionEnter, this, std::placeholders::_1));
		break;
	}
	case ColliderType::CIRCLE:
	{
		//_collider = new Collider2D(shape, _width / 2);

		_collider = AddComponent<Collider2D>(new Collider2D(shape, { width / 2 }));
		_collider->SetOnCollisionCallback(std::bind(&BasePickUp::OnCollisionEnter, this, std::placeholders::_1));
		break;
	}
	}

	if (_collider)
	{
		CollisionManager::RegisterCollider(_collider);
	}

}

