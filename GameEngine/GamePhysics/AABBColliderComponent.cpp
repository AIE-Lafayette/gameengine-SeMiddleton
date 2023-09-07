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

    GameMath::Vector3 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    if(distance > other->getRadius() + getRadius())
    return nullptr;

    GamePhysics::Collision* collisionData = new GamePhysics::Collision();

    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();

    return collisionData;
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	
}

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