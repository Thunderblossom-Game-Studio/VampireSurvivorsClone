#pragma once

#include "../Templates/Singleton.h"

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