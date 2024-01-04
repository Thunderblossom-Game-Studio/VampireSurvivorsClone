#include "Pause.h"
#include "../Core/Game.h"

//Generate the Pause Menu
Pause::Pause() 
{
    resume = new Button(-10, 0, 10, 10);
	quit = new Button(10, 0, 10, 10);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Pause::SetAlpha(bool menuActive)
{
    if (menuActive == true)
    {
        resume->SetY(0);
        quit->SetY(0);
    }
    else
    {
        resume->SetY(-200);
        quit->SetY(-200);
    }
}

//Freeze the game world
void Pause::ToggleGameWorldFreeze() {
   //set _freeze to true in game.cpp
    //Game::instance()._player->UnbindPlayerInput();
    std::cout << "Toggling Game World Freeze\n";
}

//Unfreeze the game world
void Pause::UnfreezeGameWorld() 
{
	// Code to unfreeze the game world goes here
    //Game::instance()._player->BindPlayerInput();
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
    if (menuActive == true)
    {
        if (menuValue == 1)
        {
			//Resume Game
            menuActive = false;
            Pause::SetAlpha(false);
            UnfreezeGameWorld();
		}
        if (menuValue == 2)
        {
			//Quit Game
            menuActive = false;
			Pause::SetAlpha(false);
			UnfreezeGameWorld();
            UnbindPause();
            //Add code to use IsRunning to quit the game
            //Game::instance().Cleanup();

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
    if (menuActive == false)
    {
        if (menuValue == 1)
        {
			resume->SetHighlighted();
		}
        if (menuValue == 2)
		{
            quit->SetHighlighted();
		}
        menuActive = true;
        Pause::SetAlpha(true);
        Pause::ToggleGameWorldFreeze();
    }
    else
    {
        menuActive = false;
        Pause::SetAlpha(false);
        Pause::UnfreezeGameWorld();
    }
}

Pause::~Pause()
{
    delete resume;
    delete quit;
}