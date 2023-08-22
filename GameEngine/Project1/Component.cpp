#include "Component.h"

void GameEngine::Component::addComponent(Component* component)
{

}

void GameEngine::Component::setEnable(bool value)
{
	if (!m_enabled && value == true)
		onEnable();
	else if (m_enabled && value == false)
		onDisable();


	m_enabled = onEnable;
}
