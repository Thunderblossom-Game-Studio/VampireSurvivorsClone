#pragma once

#include <SDL.h>

class Button {
public:
    Button(int x, int y, int width, int height);

    // Standard render call
    void Render(SDL_Renderer* renderer);

    // Enable/Disable alpha
    void SetAlpha(bool enable);

    // Set the button state to highlighted
    void SetHighlighted();

    // Set the button state to selected/pressed
    void SetSelected();

    // Reset the button state to its default
    void ResetState();

private:
    SDL_Rect rect;            // Position and dimensions of the button
    SDL_Color baseColor;      // Default color of the button
    SDL_Color highlightColor; // Color when highlighted
    SDL_Color selectColor;    // Color when selected/pressed
    Uint8 alpha;              // Alpha value for transparency
    bool isVisible = true;    // Flag to determine if the button is visible
    bool isSelected;          // Flag to determine if the button is selected
};
