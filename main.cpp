#include <iostream> // std::cout, std::endl
#include "Core/Game.h"
#include "Core/AudioSystem.h"

int main(int argc, char* argv[])
{
    AudioSystem::getInstance().InitializeAudioSystem();
    bool running = Game::instance().Init();
    if (!running)
    {
        std::cout << "Game::Init failed" << std::endl;
        return -1;
    }

    AudioSystem::getInstance().LoadAudio("BackroundMusic", "Assets/383_Banshees_Lair.mp3");
    AudioSystem::getInstance().LoadAudio("SoundEffect01", "Assets/jeff.wav");

    // Temp lifespan to kill the game loop after a certain amount of time
    // TODO: replace with Game::instance().IsRunning()
    //int lifespan = 100;

    AudioSystem::getInstance().PlayAudio(-1, "BackroundMusic", 0);
    while (running)
    {
        //lifespan--;
        Game::instance().Update();
        running = Game::instance().IsRunning();
    }
    AudioSystem::getInstance().CleanAudioSystem();
    return 0;
}

