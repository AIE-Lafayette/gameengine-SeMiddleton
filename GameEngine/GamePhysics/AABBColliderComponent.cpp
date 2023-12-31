#include "AABBColliderComponent.h"
#include <GameMath/Vector3.h>
#include "Project1/TransformComponent.h"
#include <Raylib/raylib.h>
#include "Project1/Engine.h"
#include "Project1/Scene.h"
#include "CircleColliderComponent.h"


//Checks collision against a circle collider
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

    //Step 1: CirclePosition - BoxPosition = BoxToCircle
	GameMath::Vector3 direction = otherPosition - position;

	//Step 2: Clamp BoxToCircle
	//if the box to circle is more than the box's x, -x, y, or -y then it needs to be set to the 
	//box's x, -x, y, or -y divided by 2.

	if (direction.x >= m_width / 2)
	{
		direction.x = m_width;
	}

	else if (direction.x >= -m_width / 2)
	{
		direction.x = -m_width;
	}

	if (direction.x >= m_height / 2)
	{
		direction.x = m_height;
	}

	else if (direction.x >= -m_height / 2)
	{
		direction.x = -m_height;
	}

	//Step 3: Add the BTC to the BP
	GameMath::Vector3 closestPoint = direction + position;


	//Step 4: CircleToPoint collision check
	//Should just be point position - circle position

	GameMath::Vector3 circleToPoint = closestPoint - other->getOwner()->getTransform()->getGlobalPosition();

	float distance = circleToPoint.getMagnitude();

	if (distance > other->getRadius())
	{
		return nullptr;
	}


    GamePhysics::Collision* collisionData = new GamePhysics::Collision();

    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = other->getRadius() - distance;

    return collisionData;
}

//Checks collision against an AABB collider
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

	bool isColliding = getRight() > other->getLeft() &&
		getBottom() < other->getTop() &&
		getTop() > other->getBottom() &&
		getLeft() < other->getRight();

	if (!isColliding)
	{
		return nullptr;
	}

	GameMath::Vector3 otherToAABB = other->getOwner()->getTransform()->getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();

	if (otherToAABB.x > m_width / 2)
	{
		otherToAABB.x = m_width / 2;
	}
	else if (otherToAABB.x < -m_width / 2)
	{
		otherToAABB.x = -m_width / 2;
	}
	if (otherToAABB.y > m_height / 2)
	{
		otherToAABB.y = m_height / 2;
	}
	else if (otherToAABB.y < -m_height / 2)
	{
		otherToAABB.y = -m_height / 2;
	}

	GameMath::Vector3 closestPoint = getOwner()->getTransform()->getGlobalPosition() + otherToAABB;

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = otherPosition - position;

	float distance = direction.getMagnitude();

	collisionData->contactPoint = closestPoint;
	collisionData->normal = getPenetrationVector(other).getNormalized();
	collisionData->penetrationDistance = getPenetrationVector(other).getMagnitude();

}

//Draws a rectangle
void GamePhysics::AABBColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	unsigned int colorCode = getColor();

	RAYLIB_H::DrawRectangleLines(getLeft(), getBottom(), m_width, m_height, GREEN);
}

//Gets the rectangle's furthest left / negative x axis
float GamePhysics::AABBColliderComponent::getLeft()
{
	return getOwner()->getTransform()->getGlobalPosition().x - m_width / 2;
}

//Gets the rectangle's furthest right / positive x axis
float GamePhysics::AABBColliderComponent::getRight()
{
	return getOwner()->getTransform()->getGlobalPosition().x + m_width / 2;
}

//Gets the rectangle's furthest top / positive y axis
float GamePhysics::AABBColliderComponent::getTop()
{
	return getOwner()->getTransform()->getGlobalPosition().y - m_height / 2;
}

//Gets the rectangle's furthest left / negative y axis
float GamePhysics::AABBColliderComponent::getBottom()
{
	return getOwner()->getTransform()->getGlobalPosition().y + m_height / 2;
}

//Gets the penetration Vector
GameMath::Vector3 GamePhysics::AABBColliderComponent::getPenetrationVector(AABBColliderComponent* other)
{
	float smallestPenetration = abs(getRight() - other->getLeft());

	GameMath::Vector3 normalFace = { 1,0,0 };

	if (abs(getLeft() - other->getRight()) < smallestPenetration)
	{
		smallestPenetration = abs(getLeft() - other->getRight());
		normalFace = { -1, 0, 0 };
	}
	if (abs(getTop() - other->getBottom()) < smallestPenetration)
	{
		smallestPenetration = abs(getTop() - other->getBottom());
		normalFace = { 0, 1, 0 };
	}
	if (abs(getBottom() - other->getTop()) < smallestPenetration)
	{
		smallestPenetration = abs(getBottom() - other->getTop());
		normalFace = { 0, -1, 0 };
	}

	return normalFace * smallestPenetration;
}