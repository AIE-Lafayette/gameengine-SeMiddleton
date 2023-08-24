#include "Entity.h"

void GameEngine::Entity::start()
{
	m_started = true;

	for (Component* component : m_components)
	{
		if 
			(component->getEnabled())
			component->start();
	}

	onStart();
}

void GameEngine::Entity::update(double deltaTime)
{
	for (Component* component : m_components)
		if (component->getEnabled())
			component->start();
}


void GameEngine::Entity::draw()
{
	//foreach()
}

void GameEngine::Entity::end()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->start();
	}
}

//void GameEngine::Entity::addComponent(Component* component)
//{
//	component->setOwner(this);
//	m_components
//}

void GameEngine::Entity::setEnabled(bool value)
{
	if (!m_enabled && value == true)
		onEnable();
	else if (m_enabled && value == false)
		onDisable();

	m_enabled = value;
}
