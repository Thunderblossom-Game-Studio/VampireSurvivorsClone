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
    delete _exampleUIObject;
    IMG_Quit();
    SDL_Quit();
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

    ret = IMG_Init(IMG_INIT_PNG);
    if (ret < 0)
    {
        std::cout << "IMG_Init failed: " << IMG_GetError() << std::endl;
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


    //// Creating example game objects for demonstration
    //_exampleGameObject = new ExampleGameObject(5, 4, 5, 5);

    //// Setting an IRenderableObject's texture. Can be done in class, just here for sake of demo.
    //_exampleGameObject->SetTexture("Assets/Textures/TextureLoadingTest.png", {128,45,16,19});

    //// UI space x,y positions are normalized and w,h scale differently to world.
    //_exampleUIObject = new ExampleGameObject(0.9f, 0.82f, 80, 80, GameRenderer::UI, { 255,0,0,255 });

    //// "Loading" a texture multiple times doesn't affect memory, the textures are stored in a catalogue and referenced 
    //// if the same filepath is used again.
    //_exampleUIObject->SetTexture("Assets/Textures/TextureLoadingTest.png", { 288,257,15,14 });

    //// Getting a renderer from the instance manager, "main" is currently the only active renderer.
    //GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");

    //// The renderer works by adding game objects to it's internal render list.
    //renderer->AddToRenderList(_exampleGameObject);
    //// You can also use 'FindInRenderList()' to get a game object and 'RemoveFromRenderList()' to remove one.
    //renderer->AddToRenderList(_exampleUIObject);

    //// Setting an object for the renderer to track. Set nullptr to not track anything.
    //renderer->SetObjectToTrack(_exampleGameObject);

    ////End of example


    _player = new Player(0,0,5,5,100,0.001);
    GameRenderer* renderer = RenderInstanceManager::instance().GetRenderer("main");
    renderer->SetObjectToTrack(_player);


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

    // Game Objects parsed into Draw function, all 'IRenderableObject' objects will be rendered to that renderer - rest ignored.
    RenderInstanceManager::instance().GetRenderer("main")->Draw();
}