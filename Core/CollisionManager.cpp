#include "CollisionManager.h"

bool CollisionManager::AABB(ICollidableObject* obj1, ICollidableObject* obj2)
{
	if(!obj1 || !obj2) return; // If either object is null, return

	Vector2 obj1Pos = obj1->GetPosition();
	Vector2 obj1Dim = obj1->GetDimensions();
	Vector2 obj2Pos = obj2->GetPosition();
	Vector2 obj2Dim = obj2->GetDimensions();

	bool isColliding = obj1Pos.x < obj2Pos.x + obj2Dim.x && 
					   obj1Pos.x + obj1Dim.x > obj2Pos.x &&
					   obj1Pos.y < obj2Pos.y + obj2Dim.y &&
					   obj1Pos.y + obj1Dim.y > obj2Pos.y;

	return isColliding; 
}

bool CollisionManager::Circle(ICollidableObject* obj1, ICollidableObject* obj2)
{
	if(!obj1 || !obj2) return; // If either object is null, return

	// Dynamic cast to circle to get radius
	ICircleCollidableObject* circle1 = dynamic_cast<ICircleCollidableObject*>(obj1); 
	ICircleCollidableObject* circle2 = dynamic_cast<ICircleCollidableObject*>(obj2); 

	float distance = (obj1->GetPosition() - obj2->GetPosition()).magnitude();
	float radiusSum = circle1->GetRadius() + circle2->GetRadius();

	return distance < radiusSum;	
}

void CollisionManager::AddCollidable(ICollidableObject* collidable)
{
	collidables.push_back(collidable);
}

void CollisionManager::HandleCollisions()
{
	for (size_t i = 0; i < collidables.size(); i++)
	{
		for (size_t j = i + 1; j < collidables.size(); j++)
		{
			if(collidables[i]->GetCollisionType() == RECTANGLE && collidables[j]->GetCollisionType() == RECTANGLE) 
			{ 

			}
			else if (collidables[i]->GetCollisionType() == RECTANGLE && collidables[j]->GetCollisionType() == CIRCLE) 
			{

			}
			else if (collidables[i]->GetCollisionType() == CIRCLE && collidables[j]->GetCollisionType() == RECTANGLE) 
			{

			}
			else if (collidables[i]->GetCollisionType() == CIRCLE && collidables[j]->GetCollisionType() == CIRCLE) 
			{ 

			}

		}
	}
}
