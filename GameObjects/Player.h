#pragma once
#include "BaseGameObject.h"
#include "IRenderableObject.h"
#include "../Core/CollisionManager.h"
#include "../Core/Collider2D.h"
#include "../Core/InputManager.h"

class Player final : public BaseGameObject, public IRenderableObject
{
private:

	Collider2D* _collider = nullptr;

public:
	float _playerHP = 0;
	float _playerMovementSpeed = 0;
	float _width = 0;
	float _height = 0;
	
	Player(float x, float y, float width, float height, float playerHP, float playerMovementSpeed, ColliderType shape = ColliderType::RECTANGLE,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~Player();

	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }
	float TimeToReset;
	bool TimeKeep = true;

	void PlayerMovementUp();
	void PlayerMovementDown();
	void PlayerMovementRight();
	void PlayerMovementLeft();

	void PlayerAutoAttack();
	void PlayerTimer();




	//void Test();
	//void PlayerInput();
	
	//void OnEnemyCollision();
	//SDL_Event _eventInput;

};

