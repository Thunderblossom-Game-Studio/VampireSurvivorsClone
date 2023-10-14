#include "ExampleGameObject.h"
#include <iostream>

#include "../Core/InputManager.h"

ExampleGameObject::ExampleGameObject(float x, float y, float width, float height, GameRenderer::RenderSpace space, SDL_Color color) : _width(width), _height(height)
{
    std::cout << "ExampleGameObject constructor" << std::endl;

    _renderSpace = space;
    _color = color;
    _position.x = x;
    _position.y = y;

    // Example of how to add a keybind - SDL_SCANCODE of the key, InputManager::KeypressType options of KEYDOWN, KEYUP and KEYHELD, and function called on keypress
    InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYDOWN, std::bind(&ExampleGameObject::SomeExampleKeybind, this));

    //InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYUP, std::bind(&ExampleGameObject::SomeExampleKeybind, this));

    //InputManager::instance().BindKey(SDL_SCANCODE_SPACE, InputManager::KeypressType::KEYHELD, std::bind(&ExampleGameObject::SomeExampleKeybind, this));

}

ExampleGameObject::~ExampleGameObject()
{
    std::cout << "ExampleGameObject destructor" << std::endl;
}

void ExampleGameObject::SomeExampleKeybind()
{
    std::cout << "ExampleGameObject::SomeExampleKeybind" << std::endl;
}