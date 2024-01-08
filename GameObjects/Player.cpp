#include <iostream>
#include "Player.h"
#include "BaseGameObject.h"
#include "IRenderableObject.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../Core/DeltaTime.h"
#include "../Core/InputManager.h"
#include "../Core/CollisionManager.h"

Player::Player(float x, float y, float width, float height, float currentXP, 
	float playerHP, float playerMovementSpeed, float playerRecoveryMultiplier, float playerArmourMultiplier, float playerDamageMultiplier,
	float playerAttackSpeedMultiplier, float playerXpMultiplier, float playerMagnetMultiplier, float playerGoldMultiplier,
	ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color) : _width(width), _height(height) , IAnimationObject("Assets/Textures/TextureLoadingTest.png", { { 129, 41, 15, 23 },
																									{ 145, 41, 15, 23 },
																									{ 161, 41, 15, 23 },      //Idle Animation!!!!!
																									{ 177, 41, 15, 23 } }, 2.0f, 1.0f)
{
	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;

	_currentXP = currentXP;
	_playerHP = playerHP;
	_playerMovementSpeed = playerMovementSpeed;
	_playerRecoveryMultiplier = playerRecoveryMultiplier;  //Health Recovery Speed_playerArmourMultiplier = playerArmourMultiplier; //Defence Multiplier Against Enemy Attacks
	_playerDamageMultiplier = playerDamageMultiplier; //Attack Multiplier Of Attacks
	_playerAttackSpeedMultiplier = playerAttackSpeedMultiplier; //Player Attack Speed
	_playerXpMultiplier = playerXpMultiplier;  //Increases Amount Of XP Gained From Drops
	_playerMagnetMultiplier = playerMagnetMultiplier; //Range to Collect Pickups
	_playerGoldMultiplier = playerGoldMultiplier;

	BindPlayerInput();

	switch (shape)
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

	SetTexture("Assets/Textures/TextureLoadingTest.png", { 128,45,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);

	std::cout << "Player Created" << std::endl;
}

Player::~Player()
{
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->RemoveFromRenderList(this);
}


void Player::PlayerMovementUp()
{
	_position.y = _position.y + (DeltaTime::GetDeltaTime() * _playerMovementSpeed);

	if (_collider)
		_collider->SetPosition(_position);
}

void Player::PlayerMovementDown()
{

	_position.y = _position.y - (DeltaTime::GetDeltaTime() * _playerMovementSpeed);

	if (_collider)
		_collider->SetPosition(_position);
}

void Player::PlayerMovementLeft()
{
	_position.x = _position.x - (DeltaTime::GetDeltaTime() * _playerMovementSpeed);

	if (_collider)
		_collider->SetPosition(_position);

	Flip(true);
}

void Player::PlayerMovementRight()
{
	_position.x = _position.x + (DeltaTime::GetDeltaTime() * _playerMovementSpeed);
	

	if (_collider)
		_collider->SetPosition(_position);

	Flip(false);
}

void Player::PlayerLevelUpOption1()
{
	if(_levelUpMenuActive == true)
	{
		//insert selection choice
	}
}

void Player::PlayerLevelUpOption2()
{
	if (_levelUpMenuActive == true)
	{
		//insert selection choice
	}
}

void Player::PlayerLevelUpOption3()
{
	if (_levelUpMenuActive == true)
	{
		//insert selection choice
	}
}

void Player::PlayerAutoAttack()
{

		std::cout << "Attack" << std::endl;
		TimeToReset = 0;
	//Insert Basic Auto Attack Here (NEEDS SPRITE & ITS OWN HIT DETECTION)
}

void Player::PlayerTimer() //This needs to be linked up to delta time
{
	//while (TimeToReset >= 0)
	//{
		TimeToReset += DeltaTime::GetDeltaTime();

		if (TimeToReset >= 0.5)
		{
			if (_defaultAttack)
			{
				delete _defaultAttack;
				_defaultAttack = nullptr;
			}

			if (Flipped() == false)
			{
				_defaultAttack = new PlayerDefaultAttack(_position.x + 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, _attackTimer, false, this, ColliderType::RECTANGLE);
				TimeToReset = 0;
			}
			else if (Flipped() == true)
			{
				_defaultAttack = new PlayerDefaultAttack(_position.x - 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, _attackTimer, true, this, ColliderType::RECTANGLE);
				TimeToReset = 0;
			}

			//if (Flipped() == false)
			//{
			//	_defaultAttack = new PlayerDefaultAttack(_position.x + 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, _attackTimer, false, ColliderType::RECTANGLE);
			//	TimeToReset = 0;
			//}
			//else if (Flipped() == true)
			//{
			//	_defaultAttack = new PlayerDefaultAttack(_position.x - 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, _attackTimer, true, ColliderType::RECTANGLE);
			//	TimeToReset = 0;
			//}

		}



		//std::cout << "Attack" << std::endl;
		//_timeToReset = 0;
		//Insert Basic Auto Attack Here (NEEDS SPRITE & ITS OWN HIT DETECTION)
	//}
}

void Player::OnCollision(Collider2D& other)
{
	if (other.GetGameObject() == _xpPickUp)
	{
		_currentXP = _currentXP + 1;
	}

}

void Player::Update(float deltaTime)
{

	if(_defaultAttack)
	{
		if(_defaultAttack->Attack())
		{
			
			//delete _defaultAttack;
			//_defaultAttack = nullptr;
			//std::cout << "Attack Deleted" << std::endl;
			//_defaultAttack->Attack();
		}
		
	}

	if (_currentXP >= _xpLevelUp)
	{
		_currentXP = 0;
		_xpLevelUp = _xpLevelUp * _xpCapMultiplier;

		//Insert harrison's Menu Function
	}

	PlayerTimer();
}

RenderInfo Player::GetRenderInfo() const
{
	return RenderInfo(_position, { _width, _height }, _texture, _src, _flipped, _sortingLayer, _color);
}

void Player::TakeDamage(float damage)
{
	_health -= damage;
}

void Player::LateUpdate(float deltaTime)
{

}

 void Player::BindPlayerInput()
{
	std::cout << "Binding player inputs" << std::endl;
	
	InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementUp, this));
	InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementLeft, this));
	InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementRight, this));
	InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementDown, this));

	InputManager::instance().BindKey(SDL_SCANCODE_1, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerLevelUpOption1, this));
	InputManager::instance().BindKey(SDL_SCANCODE_2, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerLevelUpOption2, this));
	InputManager::instance().BindKey(SDL_SCANCODE_3, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerLevelUpOption3, this));
}

void Player::UnbindPlayerInput()
{
	std::cout << "Unbinding player inputs" << std::endl;
	
	InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYHELD);
	InputManager::instance().UnbindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYHELD);
	InputManager::instance().UnbindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYHELD);
	InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYHELD);

	InputManager::instance().UnbindKey(SDL_SCANCODE_1, InputManager::KeypressType::KEYHELD);
	InputManager::instance().UnbindKey(SDL_SCANCODE_2, InputManager::KeypressType::KEYHELD);
	InputManager::instance().UnbindKey(SDL_SCANCODE_3, InputManager::KeypressType::KEYHELD);
}