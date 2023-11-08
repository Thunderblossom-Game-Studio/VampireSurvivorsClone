#include "GameWindow.h"

#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_Window, SDL_CreateWindow, SDL_DestroyWindow

GameWindow::GameWindow(token)
{
}

GameWindow::~GameWindow()
{
    SDL_DestroyWindow(_pWindow);
    std::cout << "Game window destroyed" << std::endl;
}

bool GameWindow::Init()
{
    _pWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (_pWindow == nullptr)
    {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Game window created" << std::endl;
    return true;
}