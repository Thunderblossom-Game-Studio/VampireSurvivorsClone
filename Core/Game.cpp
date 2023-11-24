#include "Game.h"
#include <iostream> // std::cout, std::endl
#include <SDL.h> // SDL_Init, SDL_Quit
#include "../Rendering/GameWindow.h"
#include "../Rendering/RenderInstanceManager.h"
#include "InputManager.h"
#include "AudioSystem.h"
#include "DeltaTime.h"
#include "LevelManager.h"

Game::Game(token)
{
    std::cout << "Game instance created" << std::endl;
}

Game::~Game()
{
    if (_map)
        delete _map;
  
    delete _exampleGameObject;
    _exampleGameObject = nullptr;
  
    // --------- Need to place these methods bellow in a compact method for organization reasons ---------
    if (_exampleGameObject)
        delete _exampleGameObject;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit(); 
    // --------- Need to place these methods above in a compact method for organization reasons ---------
    std::cout << "Game instance destroyed" << std::endl;

    //AudioSystem::instance().Cleanup();

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

    ret = TTF_Init();
    if (ret < 0)
    {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
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

    AudioSystem::instance().Init();
    
    AudioSystem::instance().LoadAudio("BackroundMusic", "Assets/383_Banshees_Lair.mp3");
    AudioSystem::instance().LoadAudio("SoundEffect01", "Assets/jeff.wav");

    _map = new TileMap("Assets/BIGMap.txt", 5);

    _player = new Player(0, 0, 5, 5,
        0, 100, 50.f, 1, 1,
        1, 1, 1, 1, 1, ColliderType::RECTANGLE);

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
        // InputManager handles keypresses, this is just a quick and dirty way to exit the game
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                _running = false;
            break;
            
        case SDL_QUIT:
            _running = false;
            break;
            
        default:
            AudioSystem::instance().PlayAudio(0, "BackroundMusic", 0);
            break;
        }
    }
  
    DeltaTime::UpdateDeltaTime();


    //TODO - Properly test Level System

    //// SDL Event handling loop
    //SDL_Event event;
    //while (SDL_PollEvent(&event))
    //{
    //    switch(event.type)
    //    {
    //    // InputManager handles keypresses, this is just a quick and dirty way to exit the game
    //    case SDL_KEYDOWN:
    //        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    //            _running = false;
    //        break;
    //        
    //    case SDL_QUIT:
    //        _running = false;
    //        break;
    //        
    //    default:
    //        break;
    //    }
    //}

}