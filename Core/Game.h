#pragma once

#include "../Templates/Singleton.h"

// Temp include for demonstration purposes
#include "../GameObjects/ExampleGameObject.h"

class GameRenderer;

class Game final : public Singleton<Game>
{
private:
    bool _running = false;

    // Temp variable for demonstration purposes
    ExampleGameObject* _exampleGameObject;

public:
    Game(token);
    ~Game();

    bool Init();
    void Update();
    bool IsRunning() const { return _running; }
};