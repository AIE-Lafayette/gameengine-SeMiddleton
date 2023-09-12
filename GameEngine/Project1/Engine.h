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
		static double getTimeStep() { return m_fixedTimeStep; }
		static void setTimeStep(float time) { m_fixedTimeStep = time; }
		static void setCurrentScene(Scene* scene) { m_currentScene = scene; }
		static Scene* getCurrentScene() { return m_currentScene; }

		static bool getApplicationShouldClose();
		static void closeApplication();

		void run();

	private:
		void start();
		void update(double deltaTime);
		void fixedUpdate();
		void draw();
		void end();

	private:
		static double m_deltaTime;
		static double m_fixedTimeStep;
		static double m_currentTime;
		static double m_accumulatedTime;
		static double m_newTime;
		static Scene* m_currentScene;
	};
}
