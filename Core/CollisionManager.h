#pragma once
#include <vector>

class Collider2D;
class CollisionManager
{
public:
	static void HandleCollisions();
	static void RegisterCollider(Collider2D* collider);

private:
	static std::vector<Collider2D*> _collidables;

	static bool CheckCollisions(Collider2D* collider1, Collider2D* collider2);

};

