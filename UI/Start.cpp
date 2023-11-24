#include "Start.h"

Button* start;
Button* quit;

// Generate the Start Menu
Start::Start()
{
    start = new Button(0, 0, 0, 0);
    quit = new Button(0, 0, 0, 0);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Start::SetAlpha(bool menuActive)
{
    if (menuActive == true)
    {
        start->alpha = 255; // Fully opaque
        quit->alpha = 255;  // Fully opaque
    }
    else
    {
        start->alpha = 0; // Fully transparent
        quit->alpha = 0;  // Fully transparent
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
            Start::SetAlpha(false);
            UnbindStart();
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
    }
}

Start::~Start()
{
    delete start;
    delete quit;
}
