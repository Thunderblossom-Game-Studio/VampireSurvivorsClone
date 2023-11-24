#include "Button.h" 
#include "HealthBar.h"

float currentHealth;
float maxHealth;
Button* health;
Button* base;
float width;
float updateWidth;

// Constructor
Bar::Bar(int x, int y, float spriteWidth)
{
    // Create a Button instance
    base = new Button(x, y, spriteWidth, spriteWidth / 4);
    // Create a Button instance
    health = new Button(x, y, spriteWidth * 0.9 , (spriteWidth / 4) * 0.9);
	//get width of health
	width = health->GetWidth();
	//width and max health = 100% of health
	//current health = 100% of maxHealth
	currentHealth = maxHealth;

}

//Update the health bar
void Bar::UpdateHealthBar(float damage)
{
	//Current health = current health - damage
	currentHealth = currentHealth - damage;
	//update width = current health / max health * width
	updateWidth = (currentHealth / maxHealth) * width;
	//set health width to update width
	health->SetWidth(updateWidth);
}

// delete the health bar
void Bar::DeleteHealthBar()
{
	delete base;
	delete health;
}