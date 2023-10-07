#pragma once
#include "Vector2.h"
#include <functional>

// Forward declaration of gameobject. Replace when main GameObject class is created
class GameObject;

enum ColliderType { NONE, RECTANGLE, CIRCLE };

class Collider2D
{
public:
	typedef std::function<void(Collider2D& other)> CollisionCallback;
	Collider2D(ColliderType type, Vector2 dimension, CollisionCallback callback = nullptr) : colliderType(type), colliderDimension(dimension) {}
	Collider2D(ColliderType type, float radius, CollisionCallback callback = nullptr) : colliderType(type), colliderRadius(radius) {}
private:
	ColliderType colliderType = NONE;
	Vector2 colliderPosition = { 0,0 };
	Vector2 colliderDimension = { 0,0 };
	float colliderRadius = 0;

	CollisionCallback onCollisionCallback = nullptr;
};

