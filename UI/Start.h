#pragma once

#include "Menu.h"

class GameMenu : public Menu 
{
public:
    GameMenu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren);
    void Execute();
};