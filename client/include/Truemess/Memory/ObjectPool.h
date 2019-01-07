#pragma once

#include <vector>
#include <stack>
#include <list>

#include <Truemess/Memory/Resource.h>

namespace tms {
class MemoryManager;

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
	template<typename Type, typename ... Args>
	typename Resource::Ptr<Type> acquire(const Args& ... args);

	/**
	 * \brief Release free memory to pool
	 * \param resource Object witch want to release memory
	 */
	void release(Resource* resource);

private:
	friend class MemoryManager;

	/**
	 * \brief Size for each frames
	 */
	size_t m_chunkSize;

	/**
	 * \brief Size of resource (sizeof(Type))
	 */
	size_t m_resourceSize;

	/**
	 * \brief Resource frames list
	 */
	std::list<typename Resource::Chunk> m_chunks;

	/**
	 * \brief Free memory for new objects
	 */
	std::stack<typename Resource::Address> m_freeAddresses;

	/**
	 * \brief Initialise first memory frame
	 * \param chunkSize Size of frame
	 */
	template<typename Type>
	void init(size_t chunkSize = 32);

	/**
	 * \brief Safe destroy all resources
	 */
	void destroy();

	/**
	 * \brief Get next free address
	 * \return Free address
	 */
	typename Resource::Address getFreeAddress();

	/**
	 * \brief Add clean frame
	 */
	void addFrame();
};

template<typename Type>
void ObjectPool::init(size_t chunkSize)
{
	m_resourceSize = sizeof(Type);
	m_chunkSize = chunkSize;
	this->addFrame();
}

template<typename Type, typename ... Args>
typename Resource::Ptr<Type> ObjectPool::acquire(const Args& ... args)
{
	Resource::Address address = getFreeAddress();

	Resource* res = new(address) Type(args...);

	res->m_objectPool = this;
	res->m_address = address;

	return Resource::Ptr<Type>(reinterpret_cast<Type*>(res));
}
}