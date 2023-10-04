#pragma once

#include "../Templates/Singleton.h"

class SDL_Window;
class SDL_Renderer;

class GameRenderer
{
private:
    SDL_Renderer* _pRenderer = nullptr;

public:
    GameRenderer(SDL_Window* pWindow);
    ~GameRenderer();

    void SetDrawColor(int r, int g, int b, int a);
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer() const { return _pRenderer; }
    virtual void Render() {};
};