#pragma once

class IRenderableObject {
protected:
    // Forward declaration of SDL_Texture to provide return type for GetTexture()
    class SDL_Texture;

public:
    virtual float GetX() const = 0;
    virtual float GetY() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual SDL_Texture* GetTexture() const = 0;
};