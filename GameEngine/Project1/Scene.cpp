#include "Scene.h"
#include "Entity.h"
#include <GamePhysics/ColliderComponent.h>

//Enables entities on start
void GameEngine::Scene::start()
{
	for (Entity* entity : m_entities)
	{
		if(entity->getEnabled())
			entity->start();
	}

	onStart();
}

//Iterates through entities, and updates / checks their collision
void GameEngine::Scene::update(double deltaTime)
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getEnabled())
			continue;

		if (!entity->getStarted())
			entity->start();

		entity->update(deltaTime);
	}
	onUpdate();

	for (auto iterator1 = m_activeColliders.begin(); iterator1 != m_activeColliders.end(); iterator1++)
	{
		for (auto iterator2 = iterator1; iterator2 != m_activeColliders.end(); iterator2++)
		{
			GamePhysics::ColliderComponent* collider1 = *iterator1;
			GamePhysics::ColliderComponent* collider2 = *iterator2;

			if (iterator1 == iterator2 || collider1->getOwner()->getEnabled() || !collider2->getOwner()->getEnabled())
				continue;

			GamePhysics::Collision* collisionData1 = nullptr;
			GamePhysics::Collision* collisionData2 = new GamePhysics::Collision();

			if (collisionData1 == collider1->checkCollision(collider2))
			{
				collider1->getOwner()->onCollisionEnter(collisionData1);

				collisionData2->collider = collider1;
				collisionData2->normal = collisionData1->normal * -1;

				collider2->getOwner()->onCollisionEnter(collisionData2);
			}
		}
	}
}

//Draws all entities to screen
void GameEngine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->draw();
	}

	onDraw();
}

//Removes all entities
void GameEngine::Scene::end()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->start();
	}
}

//Adds an entity to the scene
void GameEngine::Scene::addEntity(Entity* entity)
{
	m_entities.add(entity);
}

//Removes an entity from the scene
void GameEngine::Scene::removeEntity(Entity* entity)
{
	m_entities.remove(entity);
}
