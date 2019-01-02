#include "Core.h"

BaseManager::BaseManager(const Core& core) :
	m_core(core)
{
	std::ios_base::sync_with_stdio(false);
}

const Core& BaseManager::getCore() const
{
	return m_core;
}
