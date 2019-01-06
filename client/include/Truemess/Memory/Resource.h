#pragma once

#include <cstdint>
#include <vector>
#include <memory>

namespace tms {
template<typename T>
class ObjectPool;

/**
 * \brief Resource that stored in ObjectPool
 * \tparam Type Type of inheritor
 */
template<typename Type>
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
		void operator()(Resource<Type>* res);
	};

	/**
	 * \brief Alias std::unique_ptr<Type, Resource<Type>::Deleter>
	 */
	using Ptr = std::unique_ptr<Type, Resource<Type>::Deleter>;

	// TODO: Refactor address class
	/**
	 * \brief Address of the frame and offset of it
	 */
	class Address
	{
	public:
		Address();
		Address(typename Resource<Type>::Memory* _frame, size_t _frameOffset);

		/**
		 * \brief Pointer to the frame
		 */
		typename Resource<Type>::Memory* frame;

		/**
		 * \brief Offset in frame
		 */
		size_t frameOffset;
	};

	virtual ~Resource();

	/**
	 * \brief Get address pointer
	 * \return Address pointer
	 */
	typename Resource<Type>::Address* getAddress();

	/**
	 * \brief Get ObjectPool pointer
	 * \return ObjectPool pointer
	 */
	ObjectPool<Type>* getObjectPool();

protected:
	Resource();

private:
	friend class ObjectPool<Type>;

	/**
	 * \brief Parent pool
	 */
	ObjectPool<Type>* m_objectPool;

	/**
	 * \brief Current frame and it offset
	 */
	typename Resource<Type>::Address m_address;
};

template<typename Type>
Resource<Type>::Resource() :
	m_objectPool(nullptr)
{
}

template<typename Type>
Resource<Type>::~Resource()
{
}

template<typename Type>
typename Resource<Type>::Address* Resource<Type>::getAddress()
{
	return &m_address;
}

template<typename Type>
ObjectPool<Type>* Resource<Type>::getObjectPool()
{
	return m_objectPool;
}

template<typename Type>
inline void Resource<Type>::Deleter::operator()(Resource<Type>* res)
{
	res->getObjectPool()->release(res);
	res->~Resource<Type>();
}

template<typename Type>
Resource<Type>::Address::Address() :
	frame(nullptr),
	frameOffset(0)
{
}

template<typename Type>
Resource<Type>::Address::Address(typename Resource<Type>::Memory* _frame, size_t _frameOffset) :
	frame(_frame),
	frameOffset(_frameOffset)
{

}
}
