#pragma once

#include <cstdint>
#include <vector>
#include <memory>

namespace tms {
class ObjectPool;

/**
 * \brief Resource that stored in ObjectPool
 */
class Resource
{
public:
	/**
	 * \brief Alias std::vector<int8_t>
	 */
	using Memory = std::vector<int8_t>;

	/**
	 * \brief Deleter for std::unique_ptr
	 */
	struct Deleter
	{
		void operator()(Resource* res);
	};

	/**
	 * \brief Alias std::unique_ptr<Type, Resource<Type>::Deleter>
	 */
	template<typename Type>
	using Ptr = std::unique_ptr<Type, Resource::Deleter>;

	using Address = int8_t * ;

	virtual ~Resource();

	/**
	 * \brief Get address pointer
	 * \return Address pointer
	 */
	typename Resource::Address getAddress();

	/**
	 * \brief Get ObjectPool pointer
	 * \return ObjectPool pointer
	 */
	ObjectPool* getObjectPool();

protected:
	Resource();

private:
	friend class ObjectPool;

	/**
	 * \brief Parent pool
	 */
	ObjectPool* m_objectPool;

	/**
	 * \brief Current frame and it offset
	 */
	typename Resource::Address m_address;
};
}
