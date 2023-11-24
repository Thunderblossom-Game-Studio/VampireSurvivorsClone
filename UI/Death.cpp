#include "Death.h"

Button* restart;
Button* quitOut;

// Generate the Death Menu
Death::Death()
{
    restart = new Button(0, 0, 0, 0);
    quitOut = new Button(0, 0, 0, 0);
    SetAlpha(false);
    menuValue = 1;
}

// Enable/Disable alpha
void Death::SetAlpha(bool menuActive)
{
    if (menuActive == true)
    {
        restart->alpha = 255; // Fully opaque
        quitOut->alpha = 255;  // Fully opaque
    }
    else
    {
        restart->alpha = 0; // Fully transparent
        quitOut->alpha = 0;  // Fully transparent
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
        }
        if (menuValue == 2)
        {
            // Quit Game
            menuActive = false;
            Death::SetAlpha(false);
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
        menuActive = true;
        Death::SetAlpha(true);
    }
}

Death::~Death()
{
    delete restart;
    delete quitOut;
}
