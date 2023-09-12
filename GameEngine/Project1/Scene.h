#pragma once
#include"Entity.h"

namespace GamePhysics
{
	class ColliderComponent;
}

namespace GameEngine
{
	class Scene
	{
	public:
		Scene() { m_entities = List<Entity*>(); }

		void start();
		void update(double deltaTime);
		void fixedUpdate();
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate() {}
		virtual void onFixedUpdate() {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		void addEntity(Entity* entity);

		void removeEntity(Entity* entity);

		void addActiveCollider(GamePhysics::ColliderComponent* collider) { m_activeColliders.add(collider); }
		void removeActiveCollider(GamePhysics::ColliderComponent* collider) { m_activeColliders.remove(collider); }

	private:
		List<Entity*> m_entities;
		List<GamePhysics::ColliderComponent*> m_activeColliders;
	};

}

