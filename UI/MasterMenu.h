#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "../Core/InputManager.h"

class MasterMenu
{
    public:
    Buttons();
    ~Buttons();
    void BindDeath();
    void UnbindDeath();
    void BindStart();
    void UnbindStart();
    void BindPause();
    void UnbindPause();
    void ToggleGameWorldFreeze();
    void UnfreezeGameWorld();
    void SetAlpha(bool menuActive);
    void OpenMenu();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Execute();

private:
    Button* restart;
    Button* quitOut;
    Button* start;
    Button* quit;
    Button* resume;
    Button* unpause;
    int menuValue = 0;
    bool menuActive = false;
    bool pauseActive = false;
    bool deathActive = false;
    bool startActive = false;
};


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