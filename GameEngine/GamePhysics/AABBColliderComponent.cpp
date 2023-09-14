#include "AABBColliderComponent.h"
#include <GameMath/Vector3.h>
#include "Project1/TransformComponent.h"
#include <Raylib/raylib.h>
#include "Project1/Engine.h"
#include "Project1/Scene.h"
#include "CircleColliderComponent.h"


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

	if (direction.x >= -m_width / 2)
	{
		direction.x = -m_width;
	}

	if (direction.x >= m_height / 2)
	{
		direction.x = m_height;
	}

	if (direction.x >= -m_height / 2)
	{
		direction.x = -m_height;
	}

	//Step 3: Add the BTC to the BP
	direction + position;


	//Step 4: CircleToPoint collision check
	//Should just be point position - circle position

	CheckCollisionPointCircle();

    GamePhysics::Collision* collisionData = new GamePhysics::Collision();

    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = other->getRadius() - distance;

    return collisionData;
}



//GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
//{
//	GameMath::Vector3 otherToAABB = other.getOwner().getTransform().getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();
//
//	if()
// 
// collisionData->contactPoint = closestpoint;
// collisionData->penetrationDistance = getPenetrationVector(other).getMagnitude();
//}

void GamePhysics::AABBColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	unsigned int colorCode = getColor();

	RAYLIB_H::DrawRectangleLines(getLeft(), getBottom(), m_width, m_height, GREEN);
}

float GamePhysics::AABBColliderComponent::getLeft()
{
	return getOwner()->getTransform()->getGlobalPosition().x - m_width / 2;
}

float GamePhysics::AABBColliderComponent::getRight()
{
	return getOwner()->getTransform()->getGlobalPosition().x + m_width / 2;
}

float GamePhysics::AABBColliderComponent::getTop()
{
	return getOwner()->getTransform()->getGlobalPosition().y - m_height / 2;
}

float GamePhysics::AABBColliderComponent::getBottom()
{
	return getOwner()->getTransform()->getGlobalPosition().y + m_height / 2;
}

GameMath::Vector3 GamePhysics::AABBColliderComponent::getPenetrationVector(AABBColliderComponent* other)
{
	float smallestPenatration = abs(getRight() - other->getLeft());

	GameMath::Vector3 normalFace = { 1, 0, 0 };

	if (abs(getLeft() - other->getRight() < smallestPenatration))
	{
		smallestPenatration = abs(getLeft() - other->getRight());
		normalFace = { -1, 0, 0 };
	}
	if (abs(getTop() - other->getBottom() < smallestPenatration))
	{
		smallestPenatration = abs(getTop() - other->getBottom());
		normalFace = { 0, 1, 0 };
	}
	if (abs(getBottom() - other->getTop() < smallestPenatration))
	{
		smallestPenatration = abs(getBottom() - other->getTop());
		normalFace = { 0, -1, 0 };
	}

	return normalFace * smallestPenatration;
}