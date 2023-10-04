#pragma once

class ICollidableObject {
public:
    virtual float GetX() const = 0;
    virtual float GetY() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;
    virtual void  OnCollision(ICollidableObject* other) = 0;
};