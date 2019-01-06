#pragma once

#include <vector>
#include <stack>
#include <list>

#include <Truemess/Memory/Resource.h>

namespace tms {
class MemoryManager;

template<typename Type>
class ObjectPool
{
public:
	ObjectPool();

	/**
	 * \brief Acquire memory from pool.
	 * \tparam Args Variable pattern types
	 * \param args Arguments for constructor
	 * \return Smart unique pointer to creating object
	 */
	template<typename ... Args>
	typename Resource<Type>::Ptr acquire(const Args& ... args);

	/**
	 * \brief Release free memory to pool
	 * \param resource Object witch want to release memory
	 */
	void release(Resource<Type>* resource);

private:
	friend class MemoryManager;

	/**
	 * \brief Size for each frames
	 */
	size_t m_frameSize;

	/**
	 * \brief Size of resource (sizeof(Type))
	 */
	size_t m_resourceSize;

	/**
	 * \brief Resource frames list
	 */
	std::list<typename Resource<Type>::Memory> m_resources;

	/**
	 * \brief Free memory for new objects
	 */
	std::stack<typename Resource<Type>::Address> m_freeAddresses;

	/**
	 * \brief Initialise first memory frame
	 * \param frameSize Size of frame
	 */
	void init(size_t frameSize = 32);

	/**
	 * \brief Safe destroy all resources
	 */
	void destroy();

	/**
	 * \brief Get next free address
	 * \return Free address
	 */
	typename Resource<Type>::Address getFreeAddress();

	/**
	 * \brief Add clean frame
	 */
	void addFrame();
};

template<typename Type>
ObjectPool<Type>::ObjectPool()
{

}

template<typename Type>
void ObjectPool<Type>::init(size_t frameSize)
{
	m_resourceSize = sizeof(Type);
	m_frameSize = frameSize;
	this->addFrame();
}

template<typename Type>
void ObjectPool<Type>::destroy()
{
	// TODO: Do a safe destroying objects
	/*for (auto it = m_resources.begin(); it != m_resources.end(); ++it) {
		for (size_t offset = 0; offset < m_resources.back().size(); offset += m_resourceSize) {
			m_freeAddresses.push(Resource<Type>::Address(&m_resources.back(), offset));
		}
	}*/
}

template<typename Type>
template<typename ... Args>
typename Resource<Type>::Ptr ObjectPool<Type>::acquire(const Args& ... args)
{
	typename Resource<Type>::Address adr = getFreeAddress();

	Resource<Type>* res = new(adr) Type(args...);

	res->m_objectPool = this;
	res->m_address = adr;

	return Resource<Type>::Ptr(reinterpret_cast<Type*>(res));
}

template<typename Type>
void ObjectPool<Type>::release(Resource<Type>* resource)
{
	m_freeAddresses.push(resource->getAddress());
}

template<typename Type>
typename Resource<Type>::Address ObjectPool<Type>::getFreeAddress()
{
	if (m_freeAddresses.empty()) {
		addFrame();
	}

	typename Resource<Type>::Address address = m_freeAddresses.top();
	m_freeAddresses.pop();

	return address;
}

template<typename Type>
void ObjectPool<Type>::addFrame()
{
	m_resources.push_back(Resource<Type>::Memory(m_resourceSize * m_frameSize));

    for (auto adr = m_resources.back().begin(); adr != m_resources.back().end(); adr = std::next(adr, m_resourceSize)) {
		m_freeAddresses.push(&*adr);
    }
}
}