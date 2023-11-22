#pragma once

#include <SDL.h>

class Slider {
public:
    Slider(int x, int y, int barWidth, int barHeight, int buttonWidth, int buttonHeight, int increments);

    // Enable/Disable alpha
    void SetAlpha(bool enable);

    // Move the button up (decrease its y-coordinate)
    void MoveUp();

    // Move the button down (increase its y-coordinate)
    void MoveDown();

    // Set the slider state to selected
    void SetSelected();

    // Reset the slider state to its default
    void ResetState();

private:
    SDL_Rect barRect;      // Position and dimensions of the slider bar
    SDL_Rect buttonRect;   // Position and dimensions of the slider button
    SDL_Color barColor{ 100, 100, 100 };      // Color of the slider bar
    SDL_Color buttonColor{ 255, 255, 255 };   // Color of the slider button
    Uint8 alpha{ 255 };      // Alpha value for transparency
    bool isVisible = true;  // Flag to determine if the slider is visible
    bool selected;          // Flag to determine if the slider is selected
    int increments;         // Number of increments in the slider
};
