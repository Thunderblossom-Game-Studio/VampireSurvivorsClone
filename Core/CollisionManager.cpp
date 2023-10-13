#include "../Core/CollisionManager.h"
#include "../Core/Collider2D.h"
#include <math.h>
#include <algorithm>
#include <iostream>

std::vector<Collider2D*> CollisionManager::_collidables;

void CollisionManager::HandleCollisions()
{
	for (int i = 0; i < _collidables.size(); i++)
	{
		for (int j = i + 1; j < _collidables.size(); j++)
		{
			if (CheckCollisions(_collidables[i], _collidables[j])) 
			{
				_collidables[i]->OnCollision(_collidables[j]); 
				_collidables[j]->OnCollision(_collidables[i]); 
			}
		}
	}
}

void CollisionManager::RegisterCollider(Collider2D* collider)
{
	_collidables.push_back(collider);
}

bool CollisionManager::CheckCollisions(Collider2D* collider1, Collider2D* collider2)
{
	if (!collider1 || !collider2)
	{
		std::cout << "CollisionManager::CheckCollisions: One of the colliders is null" << std::endl; 
		return false;
	}

	ColliderType collider1Type = collider1->GetColliderType();
	ColliderType collider2Type = collider2->GetColliderType();

	if (collider1Type == ColliderType::NONE || collider2Type == ColliderType::NONE)
	{
		std::cout << "CollisionManager::CheckCollisions: One of the colliders is NONE" << std::endl;
		return false;
	}
	else if (collider1Type == RECTANGLE && collider2Type == RECTANGLE)
	{
		// Check if the rectangles overlap on the X-axis
		bool xOverlap = (collider1->GetPosition().x + collider1->GetDimensions().x >= collider2->GetPosition().x) &&
						(collider2->GetPosition().x + collider2->GetDimensions().x >= collider1->GetPosition().x);

		// Check if the rectangles overlap on the Y-axis
		bool yOverlap = (collider1->GetPosition().y + collider1->GetDimensions().y >= collider2->GetPosition().y) &&
						(collider2->GetPosition().y + collider2->GetDimensions().y >= collider1->GetPosition().y);

		// If both axes overlap, then a collision has occurred
		return xOverlap && yOverlap;
	}
	else if (collider1Type == RECTANGLE && collider2Type == CIRCLE || collider1Type == CIRCLE && collider2Type == RECTANGLE)
	{ 
		// Retrieve the positions and dimensions of the colliders
		Vector2 rectPos, circlePos;
		Vector2 rectDim, circleDim;

		if (collider1Type == ColliderType::RECTANGLE) 
		{
			rectPos = collider1->GetPosition();
			rectDim = collider1->GetDimensions();
			circlePos = collider2->GetPosition();
			circleDim = Vector2(collider2->GetRadius() * 2, collider2->GetRadius() * 2);
		}
		else 
		{
			rectPos = collider2->GetPosition();
			rectDim = collider2->GetDimensions();
			circlePos = collider1->GetPosition();
			circleDim = Vector2(collider1->GetRadius() * 2, collider1->GetRadius() * 2);
		}

		// Calculate the closest point on the rectangle to the circle's center
		float closestX = std::clamp(circlePos.x, rectPos.x, rectPos.x + rectDim.x); 
		float closestY = std::clamp(circlePos.y, rectPos.y, rectPos.y + rectDim.y);

		// Calculate the distance between the circle's center and the closest point on the rectangle
		float distanceSquared = (circlePos - Vector2(closestX, closestY)).magnitude_squared();

		// Compare the squared distance to the squared radius
		float radiusSumSquared = (circleDim.x / 2.0f) * (circleDim.x / 2.0f);
		return distanceSquared <= radiusSumSquared; 
	}
	else if (collider1Type == CIRCLE && collider2Type == CIRCLE)
	{
		float distanceSquared = (collider1->GetPosition() - collider2->GetPosition()).magnitude_squared();
		float radiusSumSquared = (collider1->GetRadius() + collider2->GetRadius()) * (collider1->GetRadius() + collider2->GetRadius());

		return distanceSquared <= radiusSumSquared;
	}

		
}
