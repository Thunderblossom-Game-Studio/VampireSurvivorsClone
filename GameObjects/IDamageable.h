#pragma once

class IDamageable {
protected:
    float _health;

public:
    virtual void TakeDamage(float damage) = 0;
    float GetHealth() const { return _health; }
    void SetHealth(float health) { _health = health; }
};