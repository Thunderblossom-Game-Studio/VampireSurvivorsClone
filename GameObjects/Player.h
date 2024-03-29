#pragma once
#include "BaseGameObject.h"
#include "../GameObjects/IAnimationObject.h"
#include "../Components/Collider2D.h"
#include "../GameObjects/PlayerDefaultAttack.h"
#include "../Core/InputManager.h"
#include "../GameObjects/IDamageable.h"

class Player final : public BaseGameObject, public IAnimationObject, public IDamageable
{
private:

	Collider2D* _collider = nullptr;

public:

	float _width = 0;
	float _height = 0;
	float _currentXP = 0;

	//Player Stats That Can Be Increased Via Level Up:

		float _playerHP = 0;   //Max Health
		float _playerMovementSpeed = 0; //Movement Speed
		float _playerRecoveryMultiplier = 0;  //Health Recovery Speed
		float _playerArmourMultiplier = 0; //Defence Multiplier Against Enemy Attacks
		float _playerDamageMultiplier = 0; //Attack Multiplier Of Attacks
		float _playerAttackSpeedMultiplier = 0; //Player Attack Speed
		float _playerXpMultiplier = 0;  //Increases Amount Of XP Gained From Drops
		float _playerMagnetMultiplier = 0; //Range to Collect Pickups
		float _playerGoldMultiplier = 0;
		//Increases Amount Of Gold Gained From Drops
		//Drop Chance Multiplier ???
		// AoE Multiplier ???
		
	
	Player(float x, float y, float width, float height, float currentXP, 
		float playerHP, float playerMovementSpeed, float playerRecoveryMultiplier, float playerArmourMultiplier, float playerDamageMultiplier, 
		float playerAttackSpeedMultiplier, float playerXpMultiplier, float playerMagnetMultiplier, float playerGoldMultiplier,  ColliderType shape = ColliderType::RECTANGLE,

		GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = { 255,255,255,255 });
	~Player();

	float GetY() const override { return _position.y; }
	float GetX() const override { return _position.x; }

	float GetWidth() const override { return _width; }
	float GetHeight() const override { return _height; }

	float _timeToReset;
	float _xpLevelUp = 100;
	float _xpCapMultiplier = 2;
	float _attackTimer = 0.2;
	bool _timeKeep = true;
	bool _levelUpMenuActive;
	float TimeToReset;
	float XPLevelUp = 100;
	float XPCapMultiplier = 2;

	float AttackTimer = 0.5;
  
	bool TimeKeep = true;
	void PlayerMovementUp();
	void PlayerMovementDown();
	void PlayerMovementRight();
	void PlayerMovementLeft();

	void PlayerLevelUpOption1();
	void PlayerLevelUpOption2();
	void PlayerLevelUpOption3();

	void PlayerAutoAttack();
	void PlayerTimer();

	void BindPlayerInput();
	void UnbindPlayerInput();

	//void LevelUpSystem();
	void OnCollision(Collider2D& other);
	BaseGameObject* _xpPickUp = nullptr;


	void LevelUpSystem();
	virtual void Update(float deltaTime) override;


	RenderInfo GetRenderInfo() const override;
  
	void TakeDamage(float damage) override;

	//void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
  
	PlayerDefaultAttack* _defaultAttack;

	//void Test();
	//void PlayerInput();

	//void OnEnemyCollision();
	//SDL_Event _eventInput;

};
