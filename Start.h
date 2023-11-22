#pragma once

#include "Menu.h"

class GameMenu : public Menu {
public:
    GameMenu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren);

    // Override or add additional member functions specific to GameMenu
    void CustomGameMenuFunction();

    // Override HandleKeyPress to add additional functionality
    void HandleKeyPress(SDL_Event& event) override;
};