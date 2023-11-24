#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "../Core/InputManager.h"

class Start
{
public:
    Start(); // Updated constructor
    void BindStart();
    void UnbindStart();
    void Execute();
    void SetAlpha(bool menuActive);
    void OpenMenu();
    void MoveUp();
    void MoveDown();
    ~Start(); // Destructor for memory cleanup

private:
    // Add more private members and methods as needed
    Button* start;
    Button* quit;
    int menuValue = 0;
    bool menuActive = false;
};
