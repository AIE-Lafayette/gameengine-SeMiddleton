#include "Engine.h"
#include <chrono>
#include "GameGraphics/Window.h"

GameEngine::Scene* GameEngine::Engine::m_currentScene = nullptr;
double GameEngine::Engine::m_deltaTime = 0;
double GameEngine::Engine::m_fixedTimeStep = 0;

GameGraphics::Window window;

//Determines if the game should close
bool GameEngine::Engine::getApplicationShouldClose()
{
	return window.getShouldClose();
}

//Closes the application
void GameEngine::Engine::closeApplication()
{
	window.close();
}

//Determines what happens at runtime
void GameEngine::Engine::run()
{
	double accumulatedTime = 0;

	double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double deltaTime = 0;

	window = GameGraphics::Window(800, 800, "TestApplication");
	window.open();
	window.setTargetFrameRate(60);

	start();

	while (!getApplicationShouldClose())
	{
		setTimeStep(0.01);

		double fixedTimeStep = getTimeStep();

		double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		deltaTime = currentTime - lastTime;

		lastTime = currentTime;

		m_deltaTime = deltaTime / 1000;

		accumulatedTime += deltaTime;

		update(m_deltaTime);

		while (accumulatedTime >= fixedTimeStep)
		{
			fixedUpdate();
			accumulatedTime -= fixedTimeStep;
		}

		window.beginDrawing();
		draw();
		window.endDrawing();
	}

	end();

	window.close();
}

//Tells the current scene to start
void GameEngine::Engine::start()
{
	m_currentScene->start();
}

//Tells the current scene to update
void GameEngine::Engine::update(double deltaTime)
{
	m_currentScene->update(deltaTime);
}

//Tells the current scene to perform a fixed update. Used for keeping physics consistent
void GameEngine::Engine::fixedUpdate()
{
	m_currentScene->fixedUpdate();
}

//Tells the current scene to draw
void GameEngine::Engine::draw()
{
	m_currentScene->draw();
}

//Tells the scene to end
void GameEngine::Engine::end()
{
	m_currentScene->end();
}
