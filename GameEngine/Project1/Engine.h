#pragma once
#include "Scene.h"


namespace GameEngine
{
	class Scene;

	class Engine
	{
	public:
		Engine() {}

		double getDeltaTime() { return m_deltaTime; }

		static void setCurrentScene(Scene* scene) { m_currentScene = scene; }
		static Scene* getCurrentScene() { return m_currentScene; }

		static bool getApplicationShouldClose();
		static void closeApplication();

		void run();

	private:
		void start();
		void update(double deltaTime);
		void draw();
		void end();

	private:
		static double m_deltaTime;
		static Scene* m_currentScene;
	};
}
