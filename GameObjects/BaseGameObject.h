#pragma once
#include "../Vector2.h"

class Vector2;

class BaseGameObject {
protected:
    BaseGameObject() = default;

    Vector2 _position = { 0, 0 };

public:
    virtual ~BaseGameObject() = default;
};