#include <Truemess/Memory/Resource.h>
#include <Truemess/Memory/ObjectPool.h>

namespace tms {
Resource::Resource() :
	m_objectPool(nullptr)
{
}

Resource::~Resource()
{
}

typename Resource::Address Resource::getAddress()
{
	return m_address;
}

ObjectPool* Resource::getObjectPool()
{
	return m_objectPool;
}

void Resource::Deleter::operator()(Resource* res)
{
	res->getObjectPool()->release(res);
	res->~Resource();
}
}