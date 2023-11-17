#pragma once
#include <vector>

class Collider2D;
class CollisionManager
{
public:
	static void HandleCollisions();
	static void RegisterCollider(Collider2D* collider);
	static std::vector<Collider2D*> GetColliders() { return _collidables; }

private:
	static std::vector<Collider2D*> _collidables;
	//NEEDS DELETE COLLISION AS DEFAULT ATTACKS COLLISION IS LEAKING MEMORY SLIGHTLY
	static bool CheckCollisions(Collider2D* collider1, Collider2D* collider2);

};

