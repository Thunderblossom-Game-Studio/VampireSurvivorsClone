#include "Renderer.h"

#include "SDL.h"
#include "../GameObjects/IRenderableObject.h"
#include "GameWindow.h" // Game::GetWindow

#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_CreateRenderer, SDL_DestroyRenderer, SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC

GameRenderer::GameRenderer(SDL_Window* pWindow)
{
    _pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_pRenderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    }
    std::cout << "Game renderer created" << std::endl;

    _x = 0;
    _y = 0;
}

GameRenderer::~GameRenderer()
{
    SDL_DestroyRenderer(_pRenderer);
    std::cout << "Game renderer destroyed" << std::endl;
}

SDL_Rect GameRenderer::WorldToScreenSpace(SDL_Rect& transform)
{
    int w = DEFAULT_SCREEN_WIDTH, h = DEFAULT_SCREEN_HEIGHT;
    SDL_GetWindowSize(GameWindow::instance().GetWindow(), &w, &h);

    float resolutionScale[2] = {(float)w/DEFAULT_SCREEN_WIDTH, (float)h/DEFAULT_SCREEN_HEIGHT };
    float invertedScale[2] = { _scale / 100, _scale / 100 };
    float scale[2] = { _unitsOnScreen[0] * invertedScale[0], _unitsOnScreen[1] * invertedScale[1] };
    float offset[2] = { transform.x - _x, transform.y - _y };    
    float range[2] = { scale[0] - (-scale[0]), scale[1] - (-scale[1]) };

    offset[0] = offset[0] - (-scale[0] * resolutionScale[0]);
    offset[1] = offset[1] - (-scale[1] * resolutionScale[1]);

    offset[0] = offset[0] / range[0];
    offset[1] = offset[1] / range[1];

    offset[0] = offset[0] / resolutionScale[0];
    offset[1] = offset[1] / resolutionScale[1];

    SDL_Rect rect =
    { 
        (int)(w * offset[0]), (int)(h - (h * offset[1])),
        (int)(transform.w / invertedScale[0]), (int)(transform.h / invertedScale[1])
    };
    return rect;
}

SDL_Rect GameRenderer::UIToScreenSpace(float x, float y, float w, float h)
{
    int wi = DEFAULT_SCREEN_WIDTH, he = DEFAULT_SCREEN_HEIGHT;
    SDL_GetWindowSize(GameWindow::instance().GetWindow(), &wi, &he);

    float resolutionScale[2] = { (float)wi / DEFAULT_SCREEN_WIDTH, (float)he / DEFAULT_SCREEN_HEIGHT };
    float invertedScale[2] = { _scale / 100, _scale / 100 };

    float scale[2] = { (float)wi * invertedScale[0], (float)he * invertedScale[1] };
    float offset[2];
    float range[2] = { scale[0] - (-scale[0]), scale[1] - (-scale[1]) };

    float pos[2] = { range[0],range[1] };
    float window_scaling[2] = {pos[0]/(invertedScale[0] * 2),pos[1]/(invertedScale[1] * 2)};

    if (window_scaling[0] < 0)
        window_scaling[0] *= -1.0f;
    else if (window_scaling[0] == 0)
        window_scaling[0] = 1;
    if (window_scaling[1] < 0)
        window_scaling[1] *= -1.0f;
    else if (window_scaling[1] == 0)
        window_scaling[1] = 1;

    offset[0] = x * window_scaling[0] * resolutionScale[0] * invertedScale[0];
    offset[1] = y * window_scaling[1] * resolutionScale[1] * invertedScale[1];

    offset[0] = offset[0] - (-scale[0] * resolutionScale[0]);
    offset[1] = offset[1] - (-scale[1] * resolutionScale[1]);

    offset[0] = offset[0] / range[0];
    offset[1] = offset[1] / range[1];

    offset[0] = offset[0] / resolutionScale[0];
    offset[1] = offset[1] / resolutionScale[1];


    SDL_Rect rect =
    {
        (int)((float)wi * offset[0]), (int)((float)he - ((float)he * offset[1])),
        (int)(w * resolutionScale[0]), (int)(h * resolutionScale[1])
    };
    return rect;
}

void GameRenderer::SetDrawColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(_pRenderer, color.r, color.g, color.b, color.a);
}

void GameRenderer::SetDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(_pRenderer, r, g, b, a);
}

void GameRenderer::Draw(const std::vector<BaseGameObject*>& gameobjects)
{
    Clear();

    if (_layers)
        std::cout << "Layers need implementing." << std::endl;
    std::vector<IRenderableObject*> uiObjects;
    IRenderableObject* renderable;
    SDL_Rect rect;

    // Render World Objects
    for (int i = 0; i < gameobjects.size(); ++i)
    {
        renderable = dynamic_cast<IRenderableObject*>(gameobjects[i]);
        if (!renderable)
            continue;
        if (renderable->GetRenderSpace() == UI)
        {
            uiObjects.push_back(renderable);
            continue;
        }
        rect = { (int)renderable->GetX(), (int)renderable->GetY(),
            (int)renderable->GetWidth(), (int)renderable->GetHeight() };
        rect = WorldToScreenSpace(rect);
        rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
        SetDrawColor(renderable->GetColor());
        SDL_RenderFillRect(_pRenderer, &rect);
    }

    // Render UI Objects
    for (int i = 0; i < uiObjects.size(); ++i)
    {
        rect = UIToScreenSpace(uiObjects[i]->GetX(), uiObjects[i]->GetY(), uiObjects[i]->GetWidth(), uiObjects[i]->GetHeight());
        rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
        SetDrawColor(uiObjects[i]->GetColor());
        SDL_RenderFillRect(_pRenderer, &rect);
    }

    SetDrawColor(_defaultColor);
    Present();
}

void GameRenderer::Clear()
{
    SDL_RenderClear(_pRenderer);
}

void GameRenderer::Present()
{
    SDL_RenderPresent(_pRenderer);
}