#include "Player.h"
#include "BaseGameObject.h"
#include "../Rendering/RenderInstanceManager.h"
#include "../Core/InputManager.h"


Player::Player(float x, float y, float width, float height, float playerHP, float playerMovementSpeed, ColliderType shape, GameRenderer::RenderSpace space, SDL_Color color)
	: _width(width), _height(height), IAnimationObject("Assets/Textures/TextureLoadingTest.png", {	{ 129, 45, 15, 19 }, 
																									{ 144, 45, 15, 19 },
																									{ 161, 45, 15, 19 },
																									{ 177, 45, 15, 19 } }, 2.0f, 5.0f)
{
	_renderSpace = space;
	_color = color;
	_position.x = x;
	_position.y = y;
	_playerHP = playerHP;
	_playerMovementSpeed = playerMovementSpeed;

	switch (shape)
	{
	case ColliderType::RECTANGLE:
	{
		_collider = new Collider2D(shape, { _width, _height });
		_collider->SetOnCollisionCallback(nullptr);
		break;
	}
	case ColliderType::CIRCLE:
	{
		_collider = new Collider2D(shape, _width/2);
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
	_position.y = _position.y + _playerMovementSpeed;
	if (_collider)
		_collider->SetPosition(_position);
}

void Player::PlayerMovementDown()
{
	_position.y = _position.y - _playerMovementSpeed;
	if (_collider)
		_collider->SetPosition(_position);
}

void Player::PlayerMovementLeft()
{
	_position.x = _position.x - _playerMovementSpeed;
	if (_collider)
		_collider->SetPosition(_position);
}

void Player::PlayerMovementRight()
{
	_position.x = _position.x + _playerMovementSpeed;
	if (_collider)
		_collider->SetPosition(_position);
}


void Player::PlayerAutoAttack()
{
	//Insert Basic Auto Attack Here
}


//void Player::OnEnemyCollision()
//{
//	//Insert Reference To HealthSystem Here
//}

