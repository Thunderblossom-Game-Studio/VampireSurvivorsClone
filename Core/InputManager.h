#pragma once

#include "../Templates/Singleton.h"
#include <map>
#include <functional>
#include <SDL.h>

class InputManager : public Singleton<InputManager> {
private:
    // Maps of key scancodes to callback functions
    std::map<SDL_Scancode, std::function<void()>> _keyDownCallbacks;
    std::map<SDL_Scancode, std::function<void()>> _keyDownMarkedRemove;
    std::map<SDL_Scancode, std::function<void()>> _keyDownMarkedAdd;
    
    std::map<SDL_Scancode, std::function<void()>> _keyUpCallbacks;
    std::map<SDL_Scancode, std::function<void()>> _keyUpMarkedRemove;
    std::map<SDL_Scancode, std::function<void()>> _keyUpMarkedAdd;
    
    std::map<SDL_Scancode, std::function<void()>> _keyHeldCallbacks;
    std::map<SDL_Scancode, std::function<void()>> _keyHeldMarkedRemove;
    std::map<SDL_Scancode, std::function<void()>> _keyHeldMarkedAdd;

    // Keystate handling
    const Uint8* _keyStates;
    Uint8* _lastKeyStates;

    void UpdateBindings();

public:
    InputManager(token);
    ~InputManager();

    bool Init();

    enum KeypressType { KEYDOWN, KEYUP, KEYHELD };

    /// @brief Binds a key to a callback function
    /// @param Scancode 
    /// @param KeypressType 
    /// @param CallbackFunction
    void BindKey(SDL_Scancode key, KeypressType type, std::function<void()> callback);

    /// @brief Unbinds a key from a callback function
    /// @param Scancode
    /// @param KeypressType
    void UnbindKey(SDL_Scancode key, KeypressType type);

    /// @brief Unbinds all keys from all callback functions
    void UnbindAllKeys();

    /// @brief Updates the input manager
    void Update();
};