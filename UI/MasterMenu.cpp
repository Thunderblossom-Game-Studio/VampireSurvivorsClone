#include "Death.h"

Button* restart;
Button* quitOut;

// Generate the Death Menu
Death::Death()
{
    restart = new Button(0, 10, 10, 10);
    quitOut = new Button(0, -10, 10, 10);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Death::SetAlpha(bool menuActive)
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

// Bind the Death Menu to keys
void Death::BindDeath()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(&Death::MoveUp, this));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(&Death::MoveDown, this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&Death::Execute, this));
}

// Unbind the Death Menu to keys
void Death::UnbindDeath()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

// Press to select
void Death::Execute()
{
    if (menuActive == true)
    {
        if (menuValue == 1)
        {
            // Retry Game
            menuActive = false;
            Death::SetAlpha(false);
            UnbindDeath();
            // Add code to retry game
        }
        if (menuValue == 2)
        {
            // Quit Game
            menuActive = false;
            Death::SetAlpha(false);
            UnbindDeath();
            // Add code to quit game
        }
    }
}

// Press to move to the up
void Death::MoveUp()
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
void Death::MoveDown()
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

// Press to open the menu
void Death::OpenMenu()
{
    if (menuActive == false)
    {
        if (menuValue == 1)
        {
            restart->SetHighlighted();
        }
        menuActive = true;
        SetAlpha(true);
    }
}

Death::~Death()
{
    delete restart;
    delete quitOut;
}
#include "Start.h"
#include "../Core/Game.h"

Button* start;
Button* quit;

// Generate the Start Menu
Start::Start()
{
    start = new Button(0, 10, 10, 10);
    quit = new Button(0, -10, 10, 10);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Start::SetAlpha(bool menuActive)
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

// Bind the Start Menu to keys
void Start::BindStart()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN, std::bind(&Start::MoveUp, this));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN, std::bind(&Start::MoveDown, this));
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&Start::Execute, this));
}

// Unbind the Start Menu to keys
void Start::UnbindStart()
{
    InputManager::instance().UnbindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYDOWN);
    InputManager::instance().UnbindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN);
}

// Press to select
void Start::Execute()
{
    if (menuActive == true)
    {
        if (menuValue == 1)
        {
            // Start Game
            menuActive = false;
            std::cout << "Debug Message: Check 1" << std::endl;
            Start::SetAlpha(false);
            std::cout << "Debug Message: Check 2" << std::endl;
            UnbindStart();
            std::cout << "Debug Message: Check 3" << std::endl;
            Game::instance()._pause->BindPause();
            std::cout << "Debug Message: Check 4" << std::endl;
        }
        if (menuValue == 2)
        {
            // Quit Game
            menuActive = false;
            Start::SetAlpha(false);
            // Add code to quit game
        }
    }
}

// Press to move to the up
void Start::MoveUp()
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
void Start::MoveDown()
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

// Press to open the menu
void Start::OpenMenu()
{
    if (menuActive == false)
    {
        menuActive = true;
        Start::SetAlpha(true);
        //highlight selected button
        if (menuValue == 1)
        {
            start->SetHighlighted();
        }
        else
        {
            quit->SetHighlighted();
        }

    }
}

Start::~Start()
{
    delete start;
    delete quit;
}

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
    Game::instance()._player->UnbindPlayerInput();
    std::cout << "Toggling Game World Freeze\n";
}

//Unfreeze the game world
void Pause::UnfreezeGameWorld()
{
    // Code to unfreeze the game world goes here
    Game::instance()._player->BindPlayerInput();
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