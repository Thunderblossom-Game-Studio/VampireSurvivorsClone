#pragma once
#include "../Core/Vector2.h"
#include <functional>
#include "../Components/Component.h"

// Forward declaration of BaseGameObject
class BaseGameObject;

enum ColliderType { NONE, RECTANGLE, CIRCLE };

class Collider2D : public Component
{
public:
	typedef std::function<void(Collider2D& other)> CollisionCallback;
	Collider2D(ColliderType type, Vector2 dimension, CollisionCallback callback = nullptr) : _colliderType(type), _colliderDimension(dimension) {}

	Collider2D(ColliderType type, float radius, CollisionCallback callback = nullptr) : _colliderType(type), _colliderRadius(radius) {}
	~Collider2D() = default;

	void SetOnCollisionCallback(CollisionCallback callback) { _onCollisionCallback = callback; }
	void OnCollision(Collider2D* other) { if (_onCollisionCallback != nullptr) _onCollisionCallback(*other); }

	void SetGameObject(BaseGameObject* gameObject) { _gameObject = gameObject; }
	BaseGameObject* GetGameObject() { return _gameObject; }

	void SetPosition(Vector2 position) { _colliderPosition = position; }
	Vector2 GetPosition() const { return _colliderPosition; }

	ColliderType GetColliderType() const { return _colliderType; }
	float GetRadius() const { return _colliderRadius; }
	Vector2 GetDimensions() const { return _colliderDimension; }

	void SetIsEnabled(bool isEnabled) override;

	
private:
	ColliderType _colliderType = NONE;
	Vector2 _colliderPosition = { 0,0 };
	Vector2 _colliderDimension = { 0,0 };
	float _colliderRadius = 0;

	CollisionCallback _onCollisionCallback = nullptr;
	BaseGameObject* _gameObject = nullptr;
};


