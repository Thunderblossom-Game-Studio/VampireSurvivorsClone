#include <iostream> // std::cout, std::endl
#include "Core/Game.h"

int main(int argc, char* argv[])
{
    bool running = Game::instance().Init();
    if (!running)
    {
        std::cout << "Game::Init failed" << std::endl;
        return -1;
    }

    // Temp lifespan to kill the game loop after a certain amount of time
    // TODO: replace with Game::instance().IsRunning()
    //int lifespan = 100;

    while (running)
    {
        //lifespan--;
        Game::instance().Update();
        running = Game::instance().IsRunning();
    }

    return 0;
}

