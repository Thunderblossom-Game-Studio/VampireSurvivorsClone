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
            //Game::instance()._pause->BindPause();
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
