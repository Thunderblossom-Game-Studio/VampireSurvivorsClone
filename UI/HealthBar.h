#pragma once

#include <SDL.h>
#include "../Rendering/RenderInstanceManager.h"
#include "../GameObjects/IRenderableObject.h"
#include "../Core/Vector2.h"

class Bar : public IRenderableObject {
public:
    // Constructor
    Bar(int x, int y, float spriteWidth);
    
    //Update the health bar
    void UpdateHealthBar(float health);

    // delete the health bar
    void DeleteHealthBar();

    // Required for position data to be accessible by the renderer and collision systems
    float GetX() const override { return _position.x; }
    float GetY() const override { return _position.y; }

    // Required for size data to be accessible by the renderer and collision systems
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }

private:
    Vector2 _position;
    float _width;
    float _height;
};
