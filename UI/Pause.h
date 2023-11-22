#pragma once

#include "Menu.h"

class Pause : public Menu {
public:
    Pause(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren);

    // Override HandleKeyPress to add additional functionality
    void HandleKeyPress(SDL_Event& event) override;

    // Override Render to add additional rendering logic
    void Render() override;

    // Add more member functions specific to Pause

private:
    void ToggleGameWorldFreeze();
};
