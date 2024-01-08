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
