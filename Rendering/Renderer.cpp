#include "Renderer.h"

#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_CreateRenderer, SDL_DestroyRenderer, SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC
#include "GameWindow.h" // Game::GetWindow

GameRenderer::GameRenderer(SDL_Window* pWindow)
{
    _pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_pRenderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    }
    std::cout << "Game renderer created" << std::endl;
}

GameRenderer::~GameRenderer()
{
    SDL_DestroyRenderer(_pRenderer);
    std::cout << "Game renderer destroyed" << std::endl;
}

void GameRenderer::SetDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(_pRenderer, r, g, b, a);
}

void GameRenderer::Clear()
{
    SDL_RenderClear(_pRenderer);
}

void GameRenderer::Present()
{
    SDL_RenderPresent(_pRenderer);
}