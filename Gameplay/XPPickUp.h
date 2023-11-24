#pragma once
#include "../GameObjects/BasePickUp.h"
#include "../GameObjects/IAnimationObject.h"

class XPPickUp : public BaseGameObject, public IAnimationObject
{
private:

	Collider2D* _collider = nullptr;
	float _width = 0;
	float _height = 0;
	BaseGameObject* _target = nullptr;

public:

	XPPickUp(float x, float y, float width, float height, BaseGameObject* target = nullptr, ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~XPPickUp();


	//virtual void OnCollisionEnter(Collider2D& other) = 0;
	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }

	RenderInfo GetRenderInfo() const override;

	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	
	void OnCollision(Collider2D& other);
};

