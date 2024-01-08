#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "../Core/InputManager.h"

class Death
{
public:
    Death(); // Updated constructor
    void BindDeath();
    void UnbindDeath();
    void Execute();
    void SetAlpha(bool menuActive);
    void OpenMenu();
    void MoveUp();
    void MoveDown();
    ~Death(); // Destructor for memory cleanup

private:
    // Add more private members and methods as needed
    Button* restart;
    Button* quitOut;
    int menuValue = 0;
    bool menuActive = false;
};
