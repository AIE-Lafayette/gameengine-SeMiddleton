#pragma once
#include "List.h"

namespace GameEngine
{
	class Component;
	class TransformComponent;

	class Entity
	{
	public:
		Entity();

		void start();
		void update(double deltaTime);
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate() {}
		virtual void onDraw() {}
		virtual void onEnd() {}
		virtual void onEnable() {}
		virtual void onDisable() {}

		void addComponent(Component* component);

		bool getStarted() { return m_started; }
		TransformComponent* getTransform() { return m_transform; }

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool value) { m_enabled = value; }

	private:
		bool m_enabled;
		bool m_started;
		List<Component*> m_components;
		TransformComponent* m_transform;

	};
	

	template <typename T>
	inline T* Entity::addComponent()
	{
		Component* component = new T();

		component->setOwner(this);
		m_components.add(component);

		return (T*)component;
	}

	template <typename T>
	inline T* Entity::getComponent()
	{
		T* result = nullptr

			for (Component* component : m_components)
			{
				if(result = dynamic_cast<T*>(component))
			}

		return result;
	}
}
