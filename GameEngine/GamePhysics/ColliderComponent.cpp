#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "Project1/Engine.h"
#include "Project1/Scene.h"

//Assigns a collider to a chosen entity
void GamePhysics::ColliderComponent::start()
{
	GameEngine::Engine::getCurrentScene()->addActiveCollider(this);
	m_rigidBody = getOwner()->getComponent<RigidBodyComponent>();
}

//Checks to see what has collided
GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
			return checkCollisionCircle((CircleColliderComponent*) other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}

	return nullptr;
}

//Changes the color when collision occurs
void GamePhysics::ColliderComponent::onCollision(GamePhysics::Collision* other)
{
	m_color = 0XFF0000FF;
}

//Updates the collider color
void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0X00FF00FF;
}
