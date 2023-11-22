#include "Start.h"

GameMenu::GameMenu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren)
    : Menu(x, y, buttonWidth, buttonHeight, sliderWidth, sliderHeight, maxChildren) {
    // Additional initialization specific to GameMenu
}

void GameMenu::Execute()
{
    if (MenuActive = true)
    {
        if (MenuValue == 1)
        {
            //Start Game
        }
        if (MenuValue == 2)
        {
            //Quit Game
        }
    }
}