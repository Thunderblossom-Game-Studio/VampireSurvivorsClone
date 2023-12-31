#pragma once

#include "../GameObjects/Player.h"
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
    ExampleGameObject* _exampleUIObject;
    Player* _player;

public:
    Game(token);
    ~Game();

    bool Init();
    void Update();
    bool IsRunning() const { return _running; }
};