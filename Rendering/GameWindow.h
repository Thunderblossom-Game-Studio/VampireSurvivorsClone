#pragma once

#include "../Templates/Singleton.h"

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600

class SDL_Window;

class GameWindow final : public Singleton<GameWindow>
{
private:
    SDL_Window* _pWindow = nullptr;

public:
    GameWindow(token);
    ~GameWindow();

    bool Init();

    SDL_Window* GetWindow() const { return _pWindow; }
};