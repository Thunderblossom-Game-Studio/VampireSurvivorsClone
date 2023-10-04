#pragma once

class IDamageable {
private:
    int _health;

public:
    virtual void TakeDamage(int damage) = 0;
    int GetHealth() const { return _health; }
    void SetHealth(int health) { _health = health; }
};