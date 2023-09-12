#include "RigidBodyComponent.h"
#include "Project1/TransformComponent.h"
#include "ColliderComponent.h"

void GamePhysics::RigidBodyComponent::setVelocity3D(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(GameMath::Vector2 velocity)
{
	m_velocity.x = velocity.x;
	m_velocity.y = velocity.y;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector3 force)
{
	setVelocity3D(getVelocity3D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	setVelocity2D(getVelocity2D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector3 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector2 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyContactForce(GamePhysics::Collision* other)
{
	float mass = getMass();
	float massOther = other->collider->getRigidBody()->getMass();

	float displacement1 = 1;

	float penetrationDistance = other->penetrationDistance;

	if (massOther != INFINITY && !getIsKinematic())
		displacement1 = massOther / (mass + massOther);

	if (!getIsKinematic())
	{
		GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
		getOwner()->getTransform()->setLocalPosition(position - (displacement1 * other->normal * penetrationDistance));
	}

	float displacement2 = massOther;

	if (mass != INFINITY)
		displacement2 = -(mass / mass + massOther);

	if (!other->collider->getRigidBody()->getIsKinematic())
	{
		GameMath::Vector3 position = other->collider->getOwner()->getTransform()->getGlobalPosition();

		other->collider->getOwner()->getTransform()->setLocalPosition(position + (displacement2 * other->normal * penetrationDistance));
	}
}

void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	//Calculate average elasticity
	//j = force magnitude
	//Average = (elasticity1 + elasticity2) / 2

	applyContactForce(collisionData);

	//RigidBodyComponent* other = collisionData->collider->
	

	float averagedElasticity = (m_elasticity + collisionData->collider->getRigidBody()->getElasticity()) / 2;

	//j = (-(1 + e) * dot(vA - vB, n)) / (dot(n , n * (1/mA + 1/mB)))
	float forceMagnitude = (-(1 + averagedElasticity) * GameMath::Vector3::dotProduct
	(m_velocity - collisionData->collider->getRigidBody()->getVelocity3D(), collisionData->normal) /
		(GameMath::Vector3::dotProduct(collisionData->normal, 
			collisionData->normal * (1 / m_mass + 1 / collisionData->collider->getRigidBody()->getMass()))));
		


	//F = n * -j

	GameMath::Vector3 force = collisionData->normal * -forceMagnitude;


}

void GamePhysics::RigidBodyComponent::update(double deltaTime)
{
	GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + getVelocity3D() * deltaTime);

	GameMath::Vector3 gravity = { 0, getGravity(), 0 };

	applyForce(gravity * getMass());
}