#include "Game.h"
#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_Init, SDL_Quit
#include "../Rendering/GameWindow.h"
#include "../Rendering/RenderInstanceManager.h"
#include "InputManager.h"


Game::Game(token)
{
    std::cout << "Game instance created" << std::endl;
}

Game::~Game()
{
    delete _exampleGameObject;
    delete _exampleUIObject;
    std::cout << "Game instance destroyed" << std::endl;
}

bool Game::Init()
{
    bool ret = 0;

    ret = SDL_Init(SDL_INIT_EVERYTHING);
    if (ret != 0)
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    ret = GameWindow::instance().Init();
    if (!ret)
    {
        std::cout << "GameWindow::Init failed" << std::endl;
        return false;
    }

    ret = RenderInstanceManager::instance().AddRenderer("main");
    if (!ret)
    {
        std::cout << "GameRenderer::Init failed" << std::endl;
        return false;
    }

    ret = InputManager::instance().Init();
    if (!ret)
    {
        std::cout << "InputManager::Init failed" << std::endl;
        return false;
    }


    // Creating example game objects for demonstration
    _exampleGameObject = new ExampleGameObject(5, 4, 10, 10);
    // UI space x,y positions are normalized.
    _exampleUIObject = new ExampleGameObject(0.75f, 0.75f, 40, 40, GameRenderer::UI, { 255,0,0,255 });
    // End of example

    GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");

    // Setting an object for the renderer to track.
    renderer->SetObjectToTrack(_exampleGameObject);

    _running = true;
    return true;
}

void Game::Update()
{
    // SDL Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                _running = false;
                break;

            default:
                break;
        }
    }

    // Updates input state and performs any bound callbacks
    InputManager::instance().Update();

    // Rendering System Demo - vector of any amount of game objects. (Ideally declared as a member in Game class, here for demo purpose.)
    std::vector<BaseGameObject*> game_objects; 

    // Game Objects added on creation. (Again ideally right after it happens, just for demo purpose is here)
    game_objects.push_back(_exampleGameObject);
    game_objects.push_back(_exampleUIObject);

    // Game Objects parsed into Draw function, all 'IRenderableObject' objects will be rendered to that renderer - rest ignored.
    RenderInstanceManager::instance().GetRenderer("main")->Draw(game_objects);
}