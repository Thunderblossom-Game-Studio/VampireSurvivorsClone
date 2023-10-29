#include "Renderer.h"

#include "SDL.h"
#include "../GameObjects/IRenderableObject.h"
#include "GameWindow.h" // Game::GetWindow

#include "../GameObjects/ExampleGameObject.h"

#include "../Core/CollisionManager.h"
#include "../Core/Collider2D.h"
#include "../Core/InputManager.h"

#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_CreateRenderer, SDL_DestroyRenderer, SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC
#include <cmath>
#include <algorithm>

GameRenderer::GameRenderer(SDL_Window* pWindow)
{
    _pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_pRenderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    }
    std::cout << "Game renderer created" << std::endl;

    _position.x = 0;
    _position.y = 0;

    InputManager::instance().BindKey(SDL_SCANCODE_F10, InputManager::KEYDOWN, std::bind(&GameRenderer::ToggleDebugGraphics, this));
}

GameRenderer::~GameRenderer()
{
    SDL_DestroyRenderer(_pRenderer);
    std::cout << "Game renderer destroyed" << std::endl;
}

SDL_Rect GameRenderer::WorldToScreenSpace(float x, float y, float w, float h)
{
    int wi = DEFAULT_SCREEN_WIDTH, he = DEFAULT_SCREEN_HEIGHT;
    SDL_GetWindowSize(GameWindow::instance().GetWindow(), &wi, &he);

    float resolutionScale[2] = {(float)wi /DEFAULT_SCREEN_WIDTH, (float)he/DEFAULT_SCREEN_HEIGHT };// 1 1

    float scale[2] = { _unitsOnScreen[0] * _scale, _unitsOnScreen[1] * _scale }; // 10 5
    float offset[2] = { x - _position.x, y - _position.y }; // 0 0
    float range[2] = { scale[0] - (-scale[0]), scale[1] - (-scale[1]) }; // 20 10

    offset[0] = offset[0] - (-scale[0] * resolutionScale[0]); // 0 - (-10 * 1) = 10
    offset[1] = offset[1] - (-scale[1] * resolutionScale[1]); // 0 - (-5 * 1) = 5

    offset[0] = offset[0] / range[0]; // 10 / 20 = 0.5
    offset[1] = offset[1] / range[1]; // 5 / 10 = 0.5

    offset[0] = offset[0] / resolutionScale[0]; // 0.5 / 1
    offset[1] = offset[1] / resolutionScale[1]; // 0.5 / 1

    float normalDimensions[2] = { w / range[0], h / range[1] };
    normalDimensions[0] = normalDimensions[0] / resolutionScale[0];
    normalDimensions[1] = normalDimensions[1] / resolutionScale[1];

    SDL_Rect rect =
    { 
        (int)((float)wi* offset[0]), // 800 * 0.5 = 400
        (int)((float)he - (he * offset[1])), // 600 * 0.5 = 300
        (int)((float)wi * normalDimensions[0]), // 5 / 1 = 5
        (int)((float)he * normalDimensions[1])  // 5 / 1 = 5
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

    float resScaleAvg = (resolutionScale[0] + resolutionScale[1]) / 2;
    SDL_Rect rect =
    {
        (int)((float)wi * offset[0]), (int)((float)he - ((float)he * offset[1])),
        (int)(w * resScaleAvg), (int)(h * resScaleAvg)
    };
    return rect;
}

void GameRenderer::Track()
{
    float tX = _target->GetX();
    float tY = _target->GetY();

    float dir = tX - _position.x;
    if (abs(dir) > 0.01f)
        _position.x += (dir * 0.01f);
    dir = tY - _position.y;
    if (abs(dir) > 0.01f)
        _position.y += (dir * 0.01f);
}

void GameRenderer::SetDrawColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(_pRenderer, color.r, color.g, color.b, color.a);
}

void GameRenderer::SetDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(_pRenderer, r, g, b, a);
}

void GameRenderer::Draw()
{
    if (_target) 
        Track();

    if (_renderList.size() == 0)
        return;
    
    Clear();

    if (_layers)
    {
        std::stable_sort(_renderList.begin(), _renderList.end(),
            [](IRenderableObject* g1, IRenderableObject* g2) {
                return g1->GetSortingLayer() - g1->GetY() < g2->GetSortingLayer() - g2->GetY(); });
    }

    std::vector<IRenderableObject*> uiObjects;
    IRenderableObject* renderable;
    SDL_Rect rect;
    // Render World Objects
    for (int i = 0; i < _renderList.size(); ++i)
    {
        renderable = _renderList[i];
        if (!renderable)
            continue;
        else if (!renderable->GetEnabled())
            continue;
        else if (renderable->GetRenderSpace() == UI)
        {
            uiObjects.push_back(renderable);
            continue;
        }
        rect = WorldToScreenSpace(renderable->GetX(), renderable->GetY(), renderable->GetWidth(), renderable->GetHeight());
        rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
        SetDrawColor(renderable->GetColor());

        SDL_Texture* texture = renderable->GetTexture();
        if (texture) 
        {
            SDL_Rect src = renderable->GetSrc();
            SDL_RenderCopy(_pRenderer, texture, &src, &rect);
        }
        else 
        {
            SDL_RenderFillRect(_pRenderer, &rect);
        }
    }

    // Render Debug
    if (_drawWorldDebug)
        DrawWorldDebug();

    // Render UI Objects
    for (int i = 0; i < uiObjects.size(); ++i)
    {
        if (!uiObjects[i]->GetEnabled())
            continue;
        rect = UIToScreenSpace(uiObjects[i]->GetX(), uiObjects[i]->GetY(), uiObjects[i]->GetWidth(), uiObjects[i]->GetHeight());
        rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
        SetDrawColor(uiObjects[i]->GetColor());
        SDL_Texture* texture = uiObjects[i]->GetTexture();
        if (texture)
        {
            SDL_Rect src = uiObjects[i]->GetSrc();
            SDL_RenderCopy(_pRenderer, texture, &src, &rect);
        }
        else
        {
            SDL_RenderFillRect(_pRenderer, &rect);
        }
    }

    SetDrawColor(_defaultColor);
    Present();
}

bool GameRenderer::AddToRenderList(IRenderableObject* go)
{
    if (FindInRenderList(go))
        return false;
    _renderList.push_back(go);
    return true;
}

IRenderableObject* GameRenderer::FindInRenderList(IRenderableObject* go)
{
    std::vector<IRenderableObject*>::iterator it = std::find(_renderList.begin(), _renderList.end(), go);
    if (it == _renderList.end())
        return nullptr;
    return _renderList[std::distance(_renderList.begin(), it)];
}

bool GameRenderer::RemoveFromRenderList(IRenderableObject* go)
{
    if (!FindInRenderList(go))
        return false;
    _renderList.erase(std::remove(_renderList.begin(), _renderList.end(), go), _renderList.end());
    return true;
}

void GameRenderer::Clear()
{
    SDL_RenderClear(_pRenderer);
}

void GameRenderer::Present()
{
    SDL_RenderPresent(_pRenderer);
}

void GameRenderer::DrawWorldDebug()
{
    // Get All Colliders
    std::vector<Collider2D*> colliders = CollisionManager::GetColliders();

    // Render Colliders
    for (int i = 0; i < colliders.size(); ++i)
    {
        if (!colliders[i])
            continue;
        // check shape
        switch (colliders[i]->GetColliderType())
        {
        case ColliderType::RECTANGLE:
        {
            Vector2 pos = colliders[i]->GetPosition();
            Vector2 dim = colliders[i]->GetDimensions();
            SDL_Rect rect = WorldToScreenSpace(pos.x, pos.y, dim.x, dim.y);
            rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
            SetDrawColor({ 0,0,255,255 });
            SDL_RenderDrawRect(_pRenderer, &rect);
            break;
        }
        case ColliderType::CIRCLE:
        {
            Vector2 pos = colliders[i]->GetPosition();
            Vector2 dim = { colliders[i]->GetRadius(), colliders[i]->GetRadius() };
            SDL_Rect rect = WorldToScreenSpace(pos.x + dim.x/2, pos.y - dim.y/2, dim.x, dim.y);
            rect.x = rect.x - rect.w / 2; rect.y = rect.y - rect.h / 2;
            
            
            SetDrawColor({ 0,0,255,255 });
            int x = 0;
            int y = rect.w;
            int d = 3 - 2 * rect.w;
            while (y >= x) {
                SDL_RenderDrawPoint(_pRenderer, rect.x + x, rect.y + y);
                SDL_RenderDrawPoint(_pRenderer, rect.x + y, rect.y + x);
                SDL_RenderDrawPoint(_pRenderer, rect.x - x, rect.y + y);
                SDL_RenderDrawPoint(_pRenderer, rect.x - y, rect.y + x);
                SDL_RenderDrawPoint(_pRenderer, rect.x + x, rect.y - y);
                SDL_RenderDrawPoint(_pRenderer, rect.x + y, rect.y - x);
                SDL_RenderDrawPoint(_pRenderer, rect.x - x, rect.y - y);
                SDL_RenderDrawPoint(_pRenderer, rect.x - y, rect.y - x);
                if (d < 0) {
                    d += 4 * x + 6;
                }
                else {
                    d += 4 * (x - y) + 10;
                    y--;
                }
                x++;
            }
            break;
        }
        default:
            break;
        }
    } 
}
