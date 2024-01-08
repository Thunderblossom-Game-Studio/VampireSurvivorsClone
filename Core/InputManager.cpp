#include "InputManager.h"
#include <SDL.h>
#include <iostream>

void InputManager::UpdateBindings()
{
    // Moves all marked keys from add map to callback map
    for (auto& key : _keyDownMarkedAdd)
    {
        _keyDownCallbacks[key.first] = key.second;
    }
    _keyDownMarkedAdd.clear();

    for (auto& key : _keyUpMarkedAdd)
    {
        _keyUpCallbacks[key.first] = key.second;
    }
    _keyUpMarkedAdd.clear();

    for (auto& key : _keyHeldMarkedAdd)
    {
        _keyHeldCallbacks[key.first] = key.second;
    }
    _keyHeldMarkedAdd.clear();

    // Moves all marked keys from callback map to remove map
    for (auto& key : _keyDownMarkedRemove)
    {
        _keyDownCallbacks.erase(key.first);
    }
    _keyDownMarkedRemove.clear();

    for (auto& key : _keyUpMarkedRemove)
    {
        _keyUpCallbacks.erase(key.first);
    }
    _keyUpMarkedRemove.clear();

    for (auto& key : _keyHeldMarkedRemove)
    {
        _keyHeldCallbacks.erase(key.first);
    }
    _keyHeldMarkedRemove.clear();
}

InputManager::InputManager(token)
{
    _keyStates = SDL_GetKeyboardState(NULL);
    _lastKeyStates = new Uint8[SDL_NUM_SCANCODES];
    SDL_memcpy(_lastKeyStates, _keyStates, SDL_NUM_SCANCODES);
}

/// @brief Automatic cleanup of input manager
InputManager::~InputManager()
{
    UnbindAllKeys();
    delete[] _lastKeyStates;
}

/// @brief Initializes input manager
bool InputManager::Init()
{
    std::cout << "Hi Dan" << std::endl;

    return true;
}

/// @brief Binds a key to a callback function
/// @param Scancode
/// @param KeypressType
/// @param CallbackFunction
void InputManager::BindKey(SDL_Scancode key, KeypressType type, std::function<void()> callback)
{
    switch (type)
    {
    case KEYDOWN:
        _keyDownCallbacks[key] = callback;
        break;
    case KEYUP:
        _keyUpCallbacks[key] = callback;
        break;
    case KEYHELD:
        _keyHeldCallbacks[key] = callback;
        break;
    default:
        break;
    }
}

/// @brief Unbinds a key from a callback function
/// @param Scancode
/// @param KeypressType
void InputManager::UnbindKey(SDL_Scancode key, KeypressType type)
{
    switch(type)
    {
    case KEYDOWN:
        _keyDownMarkedRemove[key] = _keyDownCallbacks[key];
        break;

    case KEYUP:
        _keyUpMarkedRemove[key] = _keyUpCallbacks[key];
        break;

    case KEYHELD:
        _keyHeldMarkedRemove[key] = _keyHeldCallbacks[key];
        break;

    default:
        std::cout << "Invalid KeypressType" << std::endl;
        break;
    }
}

/// @brief Unbinds all keys
void InputManager::UnbindAllKeys()
{
    _keyDownCallbacks.clear();
    _keyUpCallbacks.clear();
    _keyHeldCallbacks.clear();

    _keyDownMarkedRemove.clear();
    _keyUpMarkedRemove.clear();
    _keyHeldMarkedRemove.clear();

    _keyDownMarkedAdd.clear();
    _keyUpMarkedAdd.clear();
    _keyHeldMarkedAdd.clear();
}

/// @brief Updates keystate and performs any bound callbacks
void InputManager::Update()
{
    _keyStates = SDL_GetKeyboardState(NULL);

    UpdateBindings();
    
    // Iterates keyDown callbacks and calls bound functions if key has been recently pressed
     for (auto& key : _keyDownCallbacks)
    {
        if (_keyStates[key.first] == 1 && _lastKeyStates[key.first] == 0)
        {
            key.second();
        }
    }

    // Iterates keyUp callbacks and calls bound functions if key has been recently released
    for (auto& key : _keyUpCallbacks)
    {
        if (_keyStates[key.first] == 0 && _lastKeyStates[key.first] == 1)
        {
            key.second();
        }
    }

    // Iterates keyHeld callbacks and calls bound functions if key is currently being held
    for (auto& key : _keyHeldCallbacks)
    {
        if (_keyStates[key.first])
        {
            key.second();
        }
    }

    SDL_memcpy(_lastKeyStates, _keyStates, SDL_NUM_SCANCODES);
}