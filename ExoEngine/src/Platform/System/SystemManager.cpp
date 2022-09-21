#include "empch.h"
#include "SystemManager.h"

EM::SystemManager::~SystemManager()
{
}

void EM::SystemManager::SystemIncrement(System* system)
{
	m_Systems.emplace_back(system);
}

void EM::SystemManager::SystemIndex(unsigned int index, System* system)
{
	m_Systems.insert(index + m_Systems.begin(), system);
}

void EM::SystemManager::DeleteSystem()
{
	for (System* system : m_Systems)
	{
		std::cout << system->GetName() << std::endl;
		system->End();
		delete system;
	}
}
