#include "CircleColliderComponent.h"
#include <GameMath/Vector3.h>
#include "Project1/TransformComponent.h"
#include <Raylib/raylib.h>
#include "Project1/Engine.h"
#include "Project1/Scene.h"



GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
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

void GamePhysics::CircleColliderComponent::draw()
{
    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

    unsigned int colorCode = getColor();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(colorCode));
}
