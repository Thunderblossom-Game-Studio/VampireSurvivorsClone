#pragma once
#include "GameObjects/BaseGameObject.h"
#include "GameObjects/ICollidableObject.h"
#include "Core/InputManager.h"

class Player : BaseGameObject
{
public:
	
	int _playerHP;
	int _playerMovementSpeed;
	
	void Test();
	void PlayerInput();
	void PlayerAutoAttack();
	void OnEnemyCollision(ICollidableObject* other);
	SDL_Event _eventInput;

};

