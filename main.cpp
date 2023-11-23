#include <iostream> // std::cout, std::endl
#include "Core/Game.h"
#include "Core/ObjectSerializer.h"
#include "GameTimer.h"
#include  "../VampireSurvivorsClone/Core/WorldTime.h"

void TestGameTimer()
{
    bool running = true;

    GameTimer timer;

    timer.AddEvent(2.0f, [&]()
        {
            std::cout << "Event 0" << std::endl;
        });

    timer.AddEvent(3.0f, [&]()
        {
            std::cout << "Event 1" << std::endl;
            // running = false;
        });

    timer.AddEvent(5.0f, [&]()
        {
            std::cout << "Event 2" << std::endl;
            running = false;
        });

    while (running)
    {
        WorldTime::Update();
        timer.Update(WorldTime::GetDeltaTime());
        timer.GetTime();
    }

}

int main(int argc, char* argv[])
{
    bool running = Game::instance().Init();
    if (!running)
    {
        std::cout << "Game::Init failed" << std::endl;
        return -1;
    }
    
    while (running)
    {
        Game::instance().Update();
        running = Game::instance().IsRunning();
    }    
    

    return 0;
}

