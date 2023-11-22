#pragma once

#include <SDL.h>
#include "../Rendering/RenderInstanceManager.h"
#include "../GameObjects/IRenderableObject.h"
#include "../Core/Vector2.h"

class Button: public IRenderableObject {
public:
    Button(float x, float y, float width, float height);

    // Enable/Disable alpha
    void SetAlpha(bool enable);

    // Set the button state to highlighted
    void SetHighlighted();

    // Set the button state to selected/pressed
    void SetSelected();

    // Reset the button state to its default
    void ResetState();

    // Required for position data to be accessible by the renderer and collision systems
    float GetX() const override { return _position.x; }
    float GetY() const override { return _position.y; }

    // Required for size data to be accessible by the renderer and collision systems
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }
private:
    SDL_Color highlightColor; // Color when highlighted
    SDL_Color selectColor;    // Color when selected/pressed
    Uint8 alpha;              // Alpha value for transparency
    bool isVisible = true;    // Flag to determine if the button is visible
    bool isSelected;          // Flag to determine if the button is selected
    Vector2 _position;
    float _width;
    float _height;
};
