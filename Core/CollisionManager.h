#pragma once
#include <vector>
#include "GameObjects/ICollidableObject.h"
#include "ICircleCollidableObject.h"

class CollisionManager
{
private:
	std::vector<ICollidableObject*> collidables;

	bool AABB(ICollidableObject* obj1, ICollidableObject* obj2);
	bool Circle(ICollidableObject* obj1, ICollidableObject* obj2);

public:
	void AddCollidable(ICollidableObject* collidable);
	void HandleCollisions();
};

