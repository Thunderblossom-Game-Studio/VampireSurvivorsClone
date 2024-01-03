#pragma once
#include "../GameObjects/BaseGameObject.h"
#include "../GameObjects/IAnimationObject.h"
#include "../Core/CollisionManager.h"
#include "../Components/Collider2D.h"
#include "../Core/InputManager.h""
#include "../GameObjects/IDamageable.h"

class PlayerDefaultAttack final : public BaseGameObject, public IRenderableObject
{
private:
	float _width = 0;
	float _height = 0;
	Collider2D* _collider = nullptr;

public:
	PlayerDefaultAttack(float x, float y, float width, float height, float attackDamage, float timeTillAttack, bool flip, ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~PlayerDefaultAttack();

	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }

	bool Attack();

	float TimeToReset;
	bool TimeKeep;
	float _attackTimer;
	float _attackDamage = 1;
	BaseGameObject* _target = nullptr;
	BaseGameObject* _xpPickUp = nullptr;

	void Update(float deltatime) override;

	void LateUpdate(float deltatime) override;

	void OnCollision(Collider2D& other);


	RenderInfo GetRenderInfo() const override;;
};

