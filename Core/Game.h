#pragma once

#include "../GameObjects/Player.h"
#include "../Templates/Singleton.h"

#include "../UI/MasterMenu.h"

// Temp include for demonstration purposes
//<<<<<<< Updated upstream
#include "../GameObjects/ExampleGameObject.h"
#include "../Rendering/TileMap.h"

#include "../GameObjects/ExampleGameObject.h"
// >>>>>>> Stashed changes

#include "../GameObjects/ExampleGameObject.h"
#include "../Rendering/TileMap.h"



class GameRenderer;
class Level;

class Game final : public Singleton<Game>
{
private:
    bool _running = false;

    // Temp variable for demonstration purposes
    ExampleGameObject* _exampleGameObject;
    ExampleGameObject* _exampleUIObject;
    Player* _player;
    TileMap* _map;
    MasterMenu* _menu;
    Level* _level;

public:
    Game(token);
    ~Game();

    bool Init();
    void Update();
    bool IsRunning() const { return _running; }

    __forceinline Player* GetPlayer() { return _player; }
};