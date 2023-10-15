#include "Player.h"

void Player::Test()
{

}

void Player::PlayerInput() //Note: Edit This Later To Link With Input Manager
{
	switch (SDL_PollEvent(&_eventInput))
	{
		//Insert DeltaTime Reference Here

	case SDL_KEYDOWN: 
		if (_eventInput.key.keysym.sym == SDLK_ESCAPE)  
		{
			//Bring Up The Pause Menu
		}

		else if (_eventInput.key.keysym.sym == SDLK_s)
		{
			//Insert Player Downward Movement
			_y = _y + _playerMovementSpeed;
		}

		else if (_eventInput.key.keysym.sym == SDLK_w)
		{
			//Insert Player Upward Movement
			_y = _y - _playerMovementSpeed;
		}

		else if (_eventInput.key.keysym.sym == SDLK_a)
		{
			//Insert Player Left Movement
			_x = _x - _playerMovementSpeed;
		}

		else if (_eventInput.key.keysym.sym == SDLK_d)
		{
			//Insert Player Right Movement
			_x = _x + _playerMovementSpeed;
		}
		break;
	default:
		break;
	}
}

void Player::PlayerAutoAttack()
{
	//Insert Basic Auto Attack Here
}

void Player::OnEnemyCollision(ICollidableObject* other)
{
	//Insert Reference To HealthSystem Here
}
