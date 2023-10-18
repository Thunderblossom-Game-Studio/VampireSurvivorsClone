#pragma once
#include "GameObjects/BaseGameObject.h"
#include "GameObjects/IRenderableObject.h"
#include "Core/CollisionManager.h"
#include "Core/InputManager.h"

class Player final : public BaseGameObject, public IRenderableObject
{
public:
	

	float _playerHP = 0;
	float _playerMovementSpeed = 0;
	float _width = 0;
	float _height = 0;
	
	Player(float x, float y, float width, float height, float playerHP, float playerMovementSpeed,
		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~Player();

	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }


	void PlayerMovementUp();
	void PlayerMovementDown();
	void PlayerMovementRight();
	void PlayerMovementLeft();

	void PlayerAutoAttack();




	//void Test();
	//void PlayerInput();
	
	//void OnEnemyCollision();
	//SDL_Event _eventInput;

};

