#include <Truemess/Memory/ObjectPool.h>

namespace tms {
ObjectPool::ObjectPool()
{

}

void ObjectPool::destroy()
{
	// TODO: Do a safe destroying objects
	/*for (auto it = m_chunks.begin(); it != m_chunks.end(); ++it) {
		for (size_t offset = 0; offset < m_chunks.back().size(); offset += m_resourceSize) {
			m_freeAddresses.push(Resource<Type>::Address(&m_chunks.back(), offset));
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
	m_chunks.emplace_back(m_resourceSize * m_chunkSize);

	for (auto adr = m_chunks.back().begin(); adr != m_chunks.back().end(); adr = std::next(adr, m_resourceSize)) {
		m_freeAddresses.push(&*adr);
	}
}
}