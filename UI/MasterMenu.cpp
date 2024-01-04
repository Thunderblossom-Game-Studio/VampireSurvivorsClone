#include "MasterMenu.h"
#include <iostream>

MasterMenu::MasterMenu()
{
    restart = new Button(0, 10, 10, 10);
    quitOut = new Button(0, -10, 10, 10);
    quitOut->highlightColor = { 200, 0, 0, 255 };
    start = new   Button(0, 10, 10, 10);
    quit = new    Button(0, -10, 10, 10);
    quit->highlightColor = { 255, 0, 0, 255 };
    resume = new  Button(-10, 0, 10, 10);
    unpause = new    Button(10, 0, 10, 10);
    unpause->highlightColor = { 255, 0, 0, 255 };
    startActive = true;
    deathActive = true;
    pauseActive = true;
    SetAlpha(false);
    deathActive = false;
    pauseActive = false;
    SetAlpha(true);
    start->SetHighlighted();
    menuValue = 1;
    menuOpen = true;
    playerY = 10;
    playerY = -10;

}

#pragma region Bindings

// Bind the Death Menu to keys
void MasterMenu::BindDeath()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveUp, this));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveDown, this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::Execute,this));
}

// Unbind the Death Menu to keys
void MasterMenu::UnbindDeath()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

// Bind the Start Menu to keys
void MasterMenu::BindStart()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveUp, this));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveDown, this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::Execute, this));
}

// Unbind the Start Menu to keys
void MasterMenu::UnbindStart()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

//Bind the Pause Menu to keys
void MasterMenu::BindPause()
{
    InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveLeft, this));
    InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::MoveRight,this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::Execute, this));
    InputManager::instance().BindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN, std::bind(&MasterMenu::OpenMenu, this));
}

//Unbind the Pause Menu to keys
void MasterMenu::UnbindPause()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN);
}
#pragma endregion


void MasterMenu::Execute()
{
    if (menuOpen == true) {
    if (startActive == true)
    {
        if (menuValue == 1)
        {
            // Start Game
            MasterMenu::UnbindStart();
            createPlayer = true;
            MasterMenu::SetAlpha(false);
            startActive = false;
            pauseActive = true;
            MasterMenu::BindPause();
            menuValue = 1;
        }
        if (menuValue == 2)
        {
            // Quit Game
            quitSet = true;
        }
    }
    if (deathActive == true)
    {
        if (menuValue == 1)
        {
            //restart game
            MasterMenu::UnbindDeath();
            createPlayer = true;
            MasterMenu::SetAlpha(false);
            deathActive = false;
            pauseActive = true;
            MasterMenu::BindPause();
            menuValue = 1;

        }
        if (menuValue == 2)
        {
            //quit to start menu
                MasterMenu::UnbindDeath();
            MasterMenu::SetAlpha(false);
            deathActive = false;
            startActive = true;
            MasterMenu::BindStart();
            menuValue = 1;
            MasterMenu::SetAlpha(true);
        }
    }
    
    if (pauseActive == true)
    {
        if (menuValue == 1)
        {
            // Resume Game
            _player->BindPlayerInput();
            pauseSet = false;
            MasterMenu::SetAlpha(false);
        }
        if (menuValue == 2)
        {
            MasterMenu::SetAlpha(false);
            pauseActive = false;
            startActive = true;
            menuValue = 1;
            playerY = _player->GetY();
            MasterMenu::SetAlpha(true);
            deletePlayer = true;
        }
    }
}
};

void MasterMenu::SetAlpha(bool menuActive)
{
    if (menuActive == true)
    {
        if (startActive == true)
        {
			start->SetY(playerY +10);
			quit->SetY(playerY -10);
			start->SetX(playerX);
			quit->SetX(playerX);
            if(menuValue == 1)
			{
                start->SetHighlighted();
                quit->ResetState();
            }
            if (menuValue == 2)
            {
				quit->SetHighlighted();
				start->ResetState();
			}
		}
        if (deathActive == true)
        {
			restart->SetY(playerY + 10);
			quitOut->SetY(playerY -10);
            restart->SetX(playerX);
            quitOut->SetX(playerX);
            if (menuValue == 1)
            {
                restart->SetHighlighted();
                quitOut->ResetState();
            }
            if (menuValue == 2)
            {
                quitOut->SetHighlighted();
                restart->ResetState();
            }
		}
        if (pauseActive == true)
        {
			resume->SetY(playerY);
			unpause->SetY(playerY);
            resume->SetX(playerX - 10);
            unpause->SetX(playerX + 10);
            if (menuValue == 1)
            {
				resume->SetHighlighted();
				unpause->ResetState();
			}
            if (menuValue == 2)
            {
				unpause->SetHighlighted();
				resume->ResetState();
			}
		}
	}
    if (menuActive == false)
    {
        if (startActive == true)
        {
			start->SetY(-2000);
			quit->SetY(-2000);
		}
        if (deathActive == true)
        {
            restart->SetY(-2000);
            quitOut->SetY(-2000);
        }
        if (pauseActive == true)
        {
			resume->SetY(-2000);
			unpause->SetY(-2000);
		}
    }
};

void MasterMenu::OpenMenu()
{
    playerX = _player->GetX();
    playerY = _player->GetY();
    if (pauseActive == true)
    {
        SetAlpha(true);
        _player->UnbindPlayerInput();
        pauseSet = true;
        menuOpen = true;
    }
};

#pragma region Move

void MasterMenu::MoveUp()
{
    if (menuOpen == true) 
    {
        if (startActive == true)
        {
            if (menuValue > 1)
            {
                menuValue--;
                start->SetHighlighted();
                quit->ResetState();
            }
        }
        if (deathActive == true)
        {
            if (menuValue > 1)
            {
                menuValue--;
                restart->SetHighlighted();
                quitOut->ResetState();
            }
        }
    }
}

// Press to move to the down
void MasterMenu::MoveDown()
{
    if (menuOpen == true)
    {
        if (startActive == true)
        {
            if (menuValue < 2)
            {
                menuValue++;
                quit->SetHighlighted();
                start->ResetState();
            }
        }
        if (deathActive == true)
        {
            if (menuValue < 2)
            {
                menuValue++;
                quitOut->SetHighlighted();
                restart->ResetState();
            }
        }
    }
}

//Press to move to the left
void MasterMenu::MoveLeft()
{
    if (menuOpen == true) 
    {
        if (pauseActive == true)
        {
            if (menuValue > 1)
            {
                menuValue--;
                resume->SetHighlighted();
                unpause->ResetState();
            }
        }
    }
}

//Press to move to the right
void MasterMenu::MoveRight()
{
    if (menuOpen == true)
    {
        if (pauseActive == true)
        {
            if (menuValue < 2)
            {
                menuValue++;
                unpause->SetHighlighted();
                resume->ResetState();
            }
        }
    }
}

#pragma endregion

//delete everyting
MasterMenu::~MasterMenu()
{
	delete restart;
	delete quitOut;
	delete start;
	delete quit;
	delete resume;
	delete unpause;
}
