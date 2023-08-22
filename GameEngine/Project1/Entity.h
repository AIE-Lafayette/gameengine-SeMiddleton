#pragma once
#include "List.h"

namespace GameEngine
{
	class Component;

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

		bool getStarted() { return m_started; }

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool value) { m_enabled = value; }

	private:
		bool m_enabled;
		bool m_started;
		List<Component*> m_components;

	};
	
}
