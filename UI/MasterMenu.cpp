// Purpose: Source file for MasterMenu.h
#include "MasterMenu.h"

MasterMenu::MasterMenu()
{
    restart = new Button(0, 10, 10, 10);
    quitOut = new Button(0, -10, 10, 10);
    start = new Button(0, 10, 10, 10);
    quit = new Button(0, -10, 10, 10);
    resume = new Button(-10, 0, 10, 10);
    quit = new Button(10, 0, 10, 10);
}

#pragma region Bindings

// Bind the Death Menu to keys
void BindDeath()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(MoveUp));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(MoveDown));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(Execute));
}

// Unbind the Death Menu to keys
void UnbindDeath()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

// Bind the Start Menu to keys
void BindStart()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(MoveUp));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(MoveDown));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(Execute));
}

// Unbind the Start Menu to keys
void UnbindStart()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

//Bind the Pause Menu to keys
void BindPause()
{
    InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN, std::bind(MoveLeft));
    InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN, std::bind(MoveRight));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(Execute));
    InputManager::instance().BindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN, std::bind(OpenMenu));
}

//Unbind the Pause Menu to keys
void UnbindPause()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_ESCAPE, InputManager::KeypressType::KEYDOWN);
}
#pragma endregion


void Execute()
{
//    if (deathActive == true)
//    {
//        if (menuValue == 1)
//        {
//            // Retry Game
//            menuActive = false;
//            SetAlpha(false);
//            UnbindDeath();
//            // Add code to retry game
//        }
//        if (menuValue == 2)
//        {
//            // Quit Game
//            menuActive = false;
//            SetAlpha(false);
//            UnbindDeath();
//            // Add code to quit game
//        }
//    }
//    if (startActive == true)
//    {
//        if (menuValue == 1)
//        {
//            // Start Game
//            menuActive = false;
//            std::cout << "Debug Message: Check 1" << std::endl;
//            Start::SetAlpha(false);
//            std::cout << "Debug Message: Check 2" << std::endl;
//            UnbindStart();
//            std::cout << "Debug Message: Check 3" << std::endl;
//            Game::instance()._pause->BindPause();
//            std::cout << "Debug Message: Check 4" << std::endl;
//        }
//        if (menuValue == 2)
//        {
//            // Quit Game
//            menuActive = false;
//            Start::SetAlpha(false);
//            // Add code to quit game
//        }
//    }
//    if (pauseActive == true)
//    {
//        if (menuValue == 1)
//        {
//			// Resume Game
//			menuActive = false;
//			Pause::SetAlpha(false);
//			UnbindPause();
//			// Add code to resume game
//		}
//        if (menuValue == 2)
//        {
//			// Quit Game
//			menuActive = false;
//			Pause::SetAlpha(false);
//			UnbindPause();
//		}
//	}
};

void SetAlpha(bool menuActive)
{
    if (startActive == true)
    {
        if (menuActive == true)
        {
			start->SetY(10);
			quit->SetY(-10);
		}
        else
        {
			start->SetY(-200);
			quit->SetY(-200);
		}
	}
    if (deathActive == true)
    {
        if (menuActive == true)
        {
			restart->SetY(10);
			quitOut->SetY(-10);
		}
        else
        {
			restart->SetY(-200);
			quitOut->SetY(-200);
		}
	}
    if (pauseActive == true)
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
};

void OpenMenu()
{
    if(menuActive == false)
    {
        if (startActive == false)
        {
            if (menuValue == 1)
            {
				restart->SetHighlighted();
			}
            else
            {

            }
        }
        if (deathActive == false)
        {
			if (menuValue == 1)
			{ 

            }
            else

        }
    }
};

#pragma region Move

void MoveUp()
{
    if (menuActive == true)
    {
        if (menuValue > 1)
        {
            menuValue--;
            restart->SetHighlighted();
            quitOut->ResetState();
        }
    }
}

// Press to move to the down
void MoveDown()
{
    if (menuActive == true)
    {
        if (menuValue < 2)
        {
            menuValue++;
            quitOut->SetHighlighted();
            restart->ResetState();
        }
    }
}

// Press to move to the up
void MoveUp()
{
    if (menuActive == true)
    {
        if (menuValue > 1)
        {
            menuValue--;
            start->SetHighlighted();
            quit->ResetState();
        }
    }
}

// Press to move to the down
void MoveDown()
{
    if (menuActive == true)
    {
        if (menuValue < 2)
        {
            menuValue++;
            quit->SetHighlighted();
            start->ResetState();
        }
    }
}

//Press to move to the left
void MoveLeft()
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
void MoveRight()
{
    if (menuActive == true)
    {
        if (menuValue < 2)
        {
            menuValue++;
            quit->SetHighlighted();
            resume->ResetState();
        }
    }

}

#pragma endregion
