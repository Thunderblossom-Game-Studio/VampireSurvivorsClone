#pragma once

class BaseGameObject {
protected:
    BaseGameObject() = default;

    float _x = 0;
    float _y = 0;

public:
    virtual ~BaseGameObject() = default;
};