#include "Game.h"
#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_Init, SDL_Quit
#include "../Rendering/GameWindow.h"
#include "../Rendering/RenderInstanceManager.h"
#include "InputManager.h"
#include "AudioSystem.h"


Game::Game(token)
{
    std::cout << "Game instance created" << std::endl;
}

Game::~Game()
{
    delete _exampleGameObject;
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


    // Creating example game object for demonstration
    _exampleGameObject = new ExampleGameObject(0, 0, 1, 1);
    // End of example

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
            case SDL_KEYDOWN:
                if (SDLK_SPACE)
                {
                    AudioSystem::getInstance().PlayAudio(-1, "SoundEffect01", 0);
                    std::cout << "Final!!!" << std::endl;
                }
                break;
            default:
                break;
        }
    }

    // Updates input state and performs any bound callbacks
    InputManager::instance().Update();

    // Placeholder render loop
    RenderInstanceManager::instance().GetRenderer("main")->Clear();
    RenderInstanceManager::instance().GetRenderer("main")->SetDrawColor(0, 255, 0, 255);
    RenderInstanceManager::instance().GetRenderer("main")->Present();
}