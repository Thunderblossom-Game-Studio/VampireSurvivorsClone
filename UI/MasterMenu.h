#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "../Core/InputManager.h"

class MasterMenu
{
    public:
    void BindDeath();
    void UnbindDeath();
    void BindStart();
    void UnbindStart();
    void BindPause();
    void UnbindPause();
    void SetAlpha(bool menuActive);
    void OpenMenu();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Execute();
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