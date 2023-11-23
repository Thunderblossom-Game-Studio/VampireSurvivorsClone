#pragma once

#include <SDL.h>
#include "../Rendering/RenderInstanceManager.h"
#include "../GameObjects/IRenderableObject.h"
#include "../Core/Vector2.h"

class Slider : public IRenderableObject {
public:
    Slider(int x, int y, int barWidth, int barHeight, int increments);

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

    // Required for position data to be accessible by the renderer and collision systems
    float GetX() const override { return _position.x; }
    float GetY() const override { return _position.y; }

    // Required for size data to be accessible by the renderer and collision systems
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }

private:
    Uint8 alpha{ 255 };      // Alpha value for transparency
    bool isVisible = true;  // Flag to determine if the slider is visible
    bool selected;          // Flag to determine if the slider is selected
    int increments;         // Number of increments in the slider
    Vector2 _position;
    float _width;
    float _height;
};
