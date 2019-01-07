#include <Truemess/Memory/ObjectPool.h>

namespace tms {
ObjectPool::ObjectPool()
{

}

void ObjectPool::destroy()
{
	// TODO: Do a safe destroying objects
	/*for (auto it = m_resources.begin(); it != m_resources.end(); ++it) {
		for (size_t offset = 0; offset < m_resources.back().size(); offset += m_resourceSize) {
			m_freeAddresses.push(Resource<Type>::Address(&m_resources.back(), offset));
		}
	}*/
}

void ObjectPool::release(Resource* resource)
{
	m_freeAddresses.push(resource->getAddress());
}

typename Resource::Address ObjectPool::getFreeAddress()
{
	if (m_freeAddresses.empty()) {
		addFrame();
	}

	Resource::Address address = m_freeAddresses.top();
	m_freeAddresses.pop();

	return address;
}

void ObjectPool::addFrame()
{
	m_resources.emplace_back(m_resourceSize * m_frameSize);

	for (auto adr = m_resources.back().begin(); adr != m_resources.back().end(); adr = std::next(adr, m_resourceSize)) {
		m_freeAddresses.push(&*adr);
	}
}
}