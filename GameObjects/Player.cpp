#include "Player.h"
#include "BaseGameObject.h"
#include "IRenderableObject.h"
#include "../Rendering/RenderInstanceManager.h"
#include <iostream>
#include "../Core/DeltaTime.h"
#include "../Core/InputManager.h"
#include "../Core/CollisionManager.h"
#include "../Rendering/RenderInstanceManager.h"
#include <iostream>

Player::Player(float x, float y, float width, float height, float currentXP, 
	float playerHP, float playerMovementSpeed, float playerRecoveryMultiplier, float playerArmourMultiplier, float playerDamageMultiplier,
	float playerAttackSpeedMultiplier, float playerXpMultiplier, float playerMagnetMultiplier, float playerGoldMultiplier,
	ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color) : _width(width), _height(height)
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

	InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementUp, this));
	InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementLeft, this));
	InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementRight, this));
	InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYHELD, std::bind(&Player::PlayerMovementDown, this));

	SetTexture("Assets/Textures/TextureLoadingTest.png", { 128,45,16,19 });
	GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
	renderer->AddToRenderList(this);


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
	_position.x = _position.x + _playerMovementSpeed;
	_position.x = _position.x + (DeltaTime::GetDeltaTime() * _playerMovementSpeed);
	

	if (_collider)
		_collider->SetPosition(_position);

	Flip(false);
}


void Player::PlayerAutoAttack()
{

		std::cout << "Attack" << std::endl;
		TimeToReset = 0;
	//Insert Basic Auto Attack Here (NEEDS SPRITE & ITS OWN HIT DETECTION)
}

void Player::PlayerTimer() //This needs to be linked up to delta time
{
	while(TimeToReset >= 0)
	{
		TimeToReset = TimeToReset + 1;

		if (TimeToReset >= 1000000)
	//if(_defaultAttack)
	//{
	//	return;
	//}

	if(Flipped() == false)
	{
		_defaultAttack = new PlayerDefaultAttack(_position.x + 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, AttackTimer, false, ColliderType::RECTANGLE);
	}
	else if (Flipped() == true)
	{
		_defaultAttack = new PlayerDefaultAttack(_position.x - 5, _position.y, 5, 5, 10 * _playerDamageMultiplier, AttackTimer, true, ColliderType::RECTANGLE);
	}
	

	std::cout << "Attack" << std::endl;
	TimeToReset = 0;
	//Insert Basic Auto Attack Here (NEEDS SPRITE & ITS OWN HIT DETECTION)
}



void Player::PlayerTimer() //This needs to be linked up to delta time
{

		TimeToReset += DeltaTime::GetDeltaTime();

		if (TimeToReset >= AttackTimer)
		{
			PlayerAutoAttack();
		}

}

void Player::Update(float deltaTime)
{

	if(_defaultAttack)
	{
		if(_defaultAttack->Attack())
		{
			
			delete _defaultAttack;
			std::cout << "Attack Deleted" << std::endl;
			/*_defaultAttack->Attack();*/
		}
		
	}

	if (_currentXP >= XPLevelUp)
	{
		_currentXP = 0;
		XPLevelUp = XPLevelUp * XPCapMultiplier;

		//Insert harrison's Menu Function
	}

	PlayerTimer();
}



RenderInfo Player::GetRenderInfo() const
{
	return RenderInfo(_position, {_width, _height}, _texture, _src, _flipped, _sortingLayer, _color);
}

void Player::TakeDamage(float damage)
{
	_health -= damage;
}

void Player::Update(float deltaTime)
{
}

void Player::LateUpdate(float deltaTime)
{

}





//void Player::OnEnemyCollision()
//{
//	//Insert Reference To HealthSystem Here
//}

