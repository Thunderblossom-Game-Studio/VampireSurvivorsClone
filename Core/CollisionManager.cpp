#include "../Core/CollisionManager.h"
#include "../Components/Collider2D.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <cmath>

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

void CollisionManager::UnregisterCollider(Collider2D* collider)
{
	for (int i = 0; i < _collidables.size(); i++)
	{
		if (_collidables[i] == collider)
		{
			_collidables.erase(_collidables.begin() + i);
			return;
		}
	}
}

bool CollisionManager::CheckCollisions(Collider2D* collider1, Collider2D* collider2)
{
	if (!collider1 || !collider2)
	{
		std::cout << "CollisionManager::CheckCollisions: One of the colliders is null" << std::endl; 
		return false;
	}
	else if (collider1 == collider2)
	{
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
		bool xOverlap = (collider1->GetPosition().x - collider1->GetDimensions().x/2 + collider1->GetDimensions().x >= collider2->GetPosition().x - collider2->GetDimensions().x / 2) &&
						(collider2->GetPosition().x - collider2->GetDimensions().x/2 + collider2->GetDimensions().x >= collider1->GetPosition().x - collider1->GetDimensions().x/2);

		// Check if the rectangles overlap on the Y-axis
		bool yOverlap = (collider1->GetPosition().y - collider1->GetDimensions().y/2 + collider1->GetDimensions().y >= collider2->GetPosition().y - collider2->GetDimensions().y / 2) &&
						(collider2->GetPosition().y - collider2->GetDimensions().y/2 + collider2->GetDimensions().y >= collider1->GetPosition().y - collider1->GetDimensions().y/2);

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
			circleDim = Vector2(collider2->GetRadius(), collider2->GetRadius());
		}
		else 
		{
			rectPos = collider2->GetPosition();
			rectDim = collider2->GetDimensions();
			circlePos = collider1->GetPosition();
			circleDim = Vector2(collider1->GetRadius(), collider1->GetRadius());
		}

		float disX = abs(circlePos.x - rectPos.x);
		float disY = abs(circlePos.y - rectPos.y);

		if (disX > (rectDim.x / 2 + circleDim.x))
			return false;
		if (disY > (rectDim.y / 2 + circleDim.x))
			return false;

		if (disX <= (rectDim.x / 2) || disY <= (rectDim.y / 2))
			return true;

		double cornerDistSq = pow(disX - rectDim.x / 2, 2) + pow(disY - rectDim.y / 2, 2);

		return cornerDistSq <= pow(circleDim.x, 2);

	}
	else if (collider1Type == CIRCLE && collider2Type == CIRCLE)
	{
		float distanceSquared = (collider1->GetPosition() - collider2->GetPosition()).magnitude_squared();
		float radiusSumSquared = (collider1->GetRadius() + collider2->GetRadius()) * (collider1->GetRadius() + collider2->GetRadius());

		return distanceSquared <= radiusSumSquared;
	}

		
}
