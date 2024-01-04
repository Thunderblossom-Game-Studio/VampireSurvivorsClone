#include "Weapon.h"
#include  <cstdlib>.

void Weapon::CreateAxe()
{
	_data.name = "Flying Axe";
	_data.isSelected = false;
	_data.damageAmount = 15.0f;
	_data.accuracy = 0.75f;
	_data.isThrowable = true;

	GenerateModifier();
}

void Weapon::CreateMace()
{
	_data.name = "Mace";
	_data.isSelected = false;
	_data.damageAmount = 25.0f;
	_data.accuracy = 1.0f;
	_data.isThrowable = false;

	GenerateModifier();
}


WeaponModifier modifierList[] = { 
	{"Sharp", 1.1f}, 
	{"Dull", 0.9f}, 
	{"", 1.0f}
};

void Weapon::GenerateModifier()
{
	size_t rand = std::rand() % 3;

	_mods = modifierList[rand];

	_data.damageAmount *= _mods.damageFactor;
}

float Weapon::Damage(float enemyHealth)
{
	if (enemyHealth == 0.0f)
	{
		std::cout << "No health passed in, no damage applied, no damage returned" << std::endl;
		return enemyHealth;
	}

	if (this->_data.name == "Mace")
	{
			enemyHealth -= this->_data.damageAmount;
			if (enemyHealth < 0.0f)
				enemyHealth = 0.0f;

			return enemyHealth;
	}

	if (this->_data.name == "Flying Axe")
	{
		enemyHealth -= this->_data.damageAmount;
		if (enemyHealth < 0.0f)
			enemyHealth = 0.0f;

		return enemyHealth;
	}
}