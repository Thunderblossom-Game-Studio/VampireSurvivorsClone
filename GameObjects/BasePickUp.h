#pragma once

#include "BaseGameObject.h"
#include "IAnimationObject.h"
#include "../Core/CollisionManager.h"
#include "../Components/Collider2D.h"

class  BasePickUp : public BaseGameObject, public IAnimationObject
{
private:

	Collider2D* _collider = nullptr;

public:

	BasePickUp(float x, float y, float width, float height, ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });

	virtual void OnCollisionEnter(Collider2D& other) = 0;
};

