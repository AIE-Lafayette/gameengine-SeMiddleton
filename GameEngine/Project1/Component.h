#pragma once
#include "Entity.h"

namespace GameEngine

{

	class Component
	{
	public:
		Component() {}

		virtual void start() {}
		virtual void update(double deltaTime) {}
		virtual void draw() {}
		virtual void end() {}
		virtual void onEnable() {}
		virtual void onDisable() {}

		void addComponent(Component* component);

		template<typename T>
		T* getComponent();

		/// <summary>
		/// returns the nullptr if the variable can't be cast as the type
		/// otherwise returns the pointer to the variable of the desired cast type
		/// dynamic_cast<type>(variable name)
		/// </summary>

		/// <summary>
		/// for (type variableName : listName)
		/// {
		/// 
		/// }
		/// </summary>

		virtual void onEnable() {}
		virtual void onDisable() {}

		bool getEnabled() { return m_enabled; }
		void setEnable(bool enabled);

		Entity* getOwner() { return m_owner; }

	private:
		void setOwner(Entity* entity) { m_owner = entity; }
		bool m_enabled;
		Entity* m_owner;
		friend Entity;
	};	
	template<typename T>
	inline T* Component::getComponent()
	{
		return getOwner();
	}
}