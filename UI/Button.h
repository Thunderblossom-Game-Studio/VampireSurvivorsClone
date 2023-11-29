#pragma once

#include <SDL.h>
#include "../Rendering/RenderInstanceManager.h"
#include "../GameObjects/IRenderableObject.h"
#include "../Core/Vector2.h"

class Button: public IRenderableObject {
public:
    Uint8 alpha;              // Alpha value for transparency
    Button(float x, float y, float width, float height);

    // Set the button state to highlighted
    void SetHighlighted();

    // Set the button state to selected/pressed
    void SetSelected();

    // Reset the button state to its default
    void ResetState();

#pragma region RenderableObject

    // Implementation of pure virtual functions from IRenderableObject
    float GetX() const override { return _position.x; }
    float GetY() const override { return _position.y; }
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }
    RenderInfo GetRenderInfo() const override
    {
        // Example implementation, adjust based on your actual rendering needs
        Vector2 position = { GetX(), GetY() };
        Vector2 size = { GetWidth(), GetHeight() };
        return RenderInfo(position, size, _texture, _src, _flipped, _sortingLayer, _color);
    }
    void SetX(float x) 
    {
        _position.x = x;
    }
    void SetY(float y)
    {
		_position.y = y;
	}
    void SetWidth(float width)
    {
		_width = width;
	}
#pragma endregion
    
private:
    SDL_Color highlightColor; // Color when highlighted
    SDL_Color selectColor;    // Color when selected/pressed
    bool isVisible = true;    // Flag to determine if the button is visible
    bool isSelected;          // Flag to determine if the button is selected
    Vector2 _position;
    float _width;
    float _height;
};
