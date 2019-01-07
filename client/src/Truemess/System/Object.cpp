#include <Truemess/System/Object.h>

namespace tms {

Object::Object() :
	m_ID(Object::nextID())
{
}

uint32_t Object::id() const
{
	return m_ID;
}

uint32_t Object::nextID()
{
	static uint32_t ID = 0;
	return ID++;
}
}