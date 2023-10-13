#pragma once

#include "BaseGameObject.h"
#include "IRenderableObject.h"
#include "ICollidableObject.h"

class ExampleGameObject final : public BaseGameObject, public IRenderableObject, public ICollidableObject
{
private:
    float _width = 0;
    float _height = 0;

public:
    ExampleGameObject(float x, float y, float width, float height, 
        GameRenderer::RenderSpace space = GameRenderer::RenderSpace::WORLD, SDL_Color color = {255,255,255,255});
    ~ExampleGameObject();

    // Required for position data to be accessible by the renderer and collision systems
    float GetX() const override { return _x; }
    float GetY() const override { return _y; }
    
    // Required for size data to be accessible by the renderer and collision systems
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }

    // Callback function for the collision system
    void OnCollision(ICollidableObject* other) override {};

    // Example function that can be bound using the input manager
    void SomeExampleKeybind();
};