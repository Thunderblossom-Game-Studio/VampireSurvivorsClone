#pragma once

#include "SDL.h"
#include "../Rendering/Renderer.h"

#include <string>

class IRenderableObject {
protected:
    // Forward declaration of SDL_Texture to provide return type for GetTexture()
    SDL_Texture* _texture{ nullptr };
    SDL_Color _color = { 255,255,255,255 };
    GameRenderer::RenderSpace _renderSpace{ GameRenderer::RenderSpace::WORLD };

public:
    virtual float GetX() const = 0;
    virtual float GetY() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;
    
    /// <summary>
    /// </summary>
    /// <returns>The view space the object is rendered to.</returns>
    GameRenderer::RenderSpace GetRenderSpace() { return _renderSpace; }
    /// <summary>
    /// </summary>
    /// <returns>The color of the object.</returns>
    SDL_Color GetColor() { return _color; }
    /// <summary> 
    /// </summary>
    /// <returns>The current texture of the renderable object.</returns>
    SDL_Texture* GetTexture() { return _texture; }
};