#pragma once

#include "../Templates/Singleton.h"
#include "../GameObjects/BaseGameObject.h"

#include "SDL.h"

#include <vector>

class SDL_Window;
class SDL_Renderer;
class IRenderableObject;

class GameRenderer : public BaseGameObject
{
private:
    float _width = 800;
    float _height = 600;
    bool _layers{ false };
    float _scale{ 5 };
    float _unitsOnScreen[2]{ 10,5 };

    SDL_Renderer* _pRenderer = nullptr;
    SDL_Color _defaultColor = { 0, 255, 0, 255 };
    
    /// <summary>
    /// Converts world space transform units into SDL screen pixel coordinates.
    /// </summary>
    /// <param name="transform">The world space transform.</param>
    /// <returns>The screen pixel space coordinates.</returns>
    SDL_Rect WorldToScreenSpace(SDL_Rect& transform);
    /// <summary>
    /// Converts UI space transform units into SDL screen pixel coordinates.
    /// </summary>
    /// <param name="x">The X position</param>
    /// <param name="y">The Y position</param>
    /// <param name="w">The object's width</param>
    /// <param name="h">The object's height</param>
    /// <returns>The screen pixel space coordinates.</returns>
    SDL_Rect UIToScreenSpace(float x, float y, float w, float h);        
    
    /// <summary>
    /// Sets the default colour the renderer clears with.
    /// </summary>
    /// <param name="color"></param>
    void SetDrawColor(SDL_Color color);
    /// <summary>
    /// Sets the default colour the renderer clears with.
    /// </summary>
    /// <param name="r">Red</param>
    /// <param name="g">Green</param>
    /// <param name="b">Blue</param>
    /// <param name="a">Alpha</param>
    void SetDrawColor(int r, int g, int b, int a);
    /// <summary>
    /// Clears the renderer.
    /// </summary>
    void Clear();
    /// <summary>
    /// Presents the renderer.
    /// </summary>
    void Present();

public:
    enum RenderSpace { WORLD, UI };

    GameRenderer(SDL_Window* pWindow);
    ~GameRenderer();

    /// <summary>
    /// Sets the default colour the renderer clears with.
    /// </summary>
    /// <param name="color"></param>
    void SetDefaultColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { _defaultColor = { r,g,b,a }; }
    /// <summary>
    /// Draws every object passed in to the renderer.
    /// </summary>
    /// <param name="gameobjects">A list of all objects wanting to be rendered in the renderer.</param>
    void Draw(const std::vector<BaseGameObject*>& gameobjects);
    /// <summary>
    /// Gets the Renderer's SDL_Renderer.
    /// </summary>
    /// <returns></returns>
    SDL_Renderer* GetRenderer() const { return _pRenderer; }

    /* Basic Renderer Movement Functions
    void MoveLeft() { _x -= .01f; }
    void MoveRight() { _x += .01f; }

    void MoveUp() { _y += .01f; }
    void MoveDown() { _y -= .01f; }

    void SetScaleOne() { _scale = 5; }
    void SetScaleTwo() { _scale = 10; }
    void SetScaleThree() { _scale = 15; }
    void SetScaleFour() { _scale = 20; }
    */
};