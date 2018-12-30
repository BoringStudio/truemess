#include "BaseManager.h"

BaseManager::BaseManager(const Core& core) :
	m_core(core)
{
}

const Core& BaseManager::getCore() const
{
	return m_core;
}
