#include "Pause.h"

Button* resume;
Button* quit;

//Generate the Pause Menu
Pause::Pause() 
{
    resume = new Button(0, 0, 0, 0);
	quit = new Button(0, 0, 0, 0);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Pause::SetAlpha(bool menuActive)
{
    if (menuActive == true)
    {
        resume->alpha = 255; // Fully opaque
        quit->alpha = 255; // Fully opaque
    }
    else
    {
        resume->alpha = 0;   // Fully transparent
        quit->alpha = 0;   // Fully transparent
    }
}

//Freeze the game world
void Pause::ToggleGameWorldFreeze() {
    // Code to freeze/unfreeze the game world goes here
    std::cout << "Toggling Game World Freeze\n";
}

//Unfreeze the game world
void Pause::UnfreezeGameWorld() 
{
	// Code to unfreeze the game world goes here
	std::cout << "Unfreezing Game World\n";
}

//Bind the Pause Menu to keys
void Pause::BindPause()
{
    InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN, std::bind(&Pause::MoveLeft, this));
    InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN, std::bind(&Pause::MoveRight, this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&Pause::Execute, this));
    InputManager::instance().BindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN, std::bind(&Pause::OpenMenu, this));
}

//Unbind the Pause Menu to keys
void Pause::UnbindPause()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN);
	InputManager::instance().UnbindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN);
}

//Press to select
void Pause::Execute()
{
    if (menuActive = true)
    {
        if (menuValue == 1)
        {
			//Resume Game
		}
        if (menuValue == 2)
        {
			//Quit Game
		}
	}
}

//Press to move to the left
void Pause::MoveLeft()
{
    if (menuActive == true)
    {
        if (menuValue > 1)
        {
		    menuValue--;
            resume->SetHighlighted();
            quit->ResetState();
	    }
    }
    
}
//Press to move to the right
void Pause::MoveRight()
{
    if(menuActive == true)
    {
        if (menuValue < 2)
        {
		    menuValue++;
			quit->SetHighlighted();
			resume->ResetState();
	    } 
    }
    
}

//Press to open the menu
void Pause::OpenMenu()
{
    if (menuActive = false)
    {
        menuActive = true;
        Pause::SetAlpha(true);
    }
    else
    {
        menuActive = false;
        Pause::SetAlpha(false);
    }
}

Pause::~Pause()
{
    delete resume;
    delete quit;
}