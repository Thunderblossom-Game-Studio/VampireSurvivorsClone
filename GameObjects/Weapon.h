#pragma once

#include "BaseGameObject.h"
#include "IRenderableObject.h"

struct WeaponData
{
	float speed;

	float damageAmount;

	float accuracy;

	bool isSelected;

	bool isThrowable;
	
	std::string name;
};

struct WeaponModifier
{
	std::string modName;

	float damageFactor = 1;
};

struct Weapon
{
	WeaponModifier _mods;

	WeaponData _data;

	void CreateAxe();

	void CreateMace();

	void GenerateModifier();

	float Damage(float enemyHealth);
};

