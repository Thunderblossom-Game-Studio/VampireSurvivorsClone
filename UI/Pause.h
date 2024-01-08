#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "../Core/InputManager.h"

class Pause
{
public:
    Pause(); // Updated constructor
    void ToggleGameWorldFreeze();
    void UnfreezeGameWorld();
    void BindPause();
    void UnbindPause();
    void Execute();
    void SetAlpha(bool menuActive);
    void OpenMenu();
    void MoveLeft();
    void MoveRight();
    ~Pause(); // Destructor for memory cleanup

private:
    // Add more private members and methods as needed
    Button* resume;
    Button* quit;
    int menuValue = 0;
    bool menuActive = false;
};
