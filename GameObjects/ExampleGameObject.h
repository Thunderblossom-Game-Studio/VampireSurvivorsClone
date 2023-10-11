#pragma once

#include "BaseGameObject.h"
#include "IRenderableObject.h"

class ExampleGameObject final : public BaseGameObject, public IRenderableObject
{
private:
    float _width = 0;
    float _height = 0;

public:
    ExampleGameObject(float x, float y, float width, float height);
    ~ExampleGameObject();

    // Required for position data to be accessible by the renderer and collision systems
    float GetY() const override { return _position.y; }
    float GetX() const override { return _position.x; }
    
    // Required for size data to be accessible by the renderer and collision systems
    float GetWidth() const override { return _width; }
    float GetHeight() const override { return _height; }

    // Storing the texture in the game object 
    SDL_Texture* GetTexture() const override { return nullptr; }

    // Callback function for the collision system
    //void OnCollision(ICollidableObject* other) override {};

    // Example function that can be bound using the input manager
    void SomeExampleKeybind();
};