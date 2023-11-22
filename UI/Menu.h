#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Button.h"
#include "SliderUI.h"
#include "../Core/InputManager.h"
int MenuValue;
bool MenuActive;

class Menu {
public:
    Menu(int x, int y, int buttonWidth, int buttonHeight, int sliderWidth, int sliderHeight, int maxChildren);

    // Render and assign value to children
    void Render();

    // Set alpha of children on/off
    void SetAlpha(bool enable);

    // Handle key presses to change highlighted button accordingly
    void HandleKeyPress(SDL_Event& event);

private:
    int x, y;               // Position of the menu
    int buttonWidth, buttonHeight; // Dimensions of buttons
    int sliderWidth, sliderHeight; // Dimensions of sliders
    int maxChildren;        // Maximum number of children (buttons and sliders) in the menu
    int activeChild;        // Index of the currently active/selected child

    std::vector<Button> buttons; // Vector to store buttons
    std::vector<Slider> sliders; // Vector to store sliders

    // Generate buttons with given location, value, and colors
    void GenerateButtons();

    // Generate sliders with given location, value, and colors
    void GenerateSliders();

    // Change the highlighted button based on the key press (Up or Down)
    void HighlightButton(int direction);
};
