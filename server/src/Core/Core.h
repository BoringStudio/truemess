#pragma once

#include <typeindex>
#include <unordered_map>
#include <memory>

#include "../Stuff/BaseManager.h"

class Core
{
public:
	Core();
	virtual ~Core();

	virtual void run() = 0;

	template<typename T, typename... Args>
	std::shared_ptr<T> provide(Args&&... args);

	template<typename T>
	std::shared_ptr<T> get() const;

	template<typename T>
	bool has() const;

private:
	std::pmr::unordered_map<std::type_index, std::shared_ptr<BaseManager>> m_managers;
};

template<typename T, typename ... Args>
std::shared_ptr<T> Core::provide(Args&&... args)
{
	static_assert(std::is_base_of<BaseManager, T>(), "Core::provide<T>: T must be derived from BaseManager");

	const auto result = std::make_shared<T>(*this, std::forward<Args>(args)...);
	m_managers.insert_or_assign(std::type_index(typeid(T)), std::dynamic_pointer_cast<BaseManager>(result));

	return result;
}

template<typename T>
std::shared_ptr<T> Core::get() const
{
	static_assert(std::is_base_of<BaseManager, T>(), "Core::get<T>: T must be derived from BaseManager");

	const auto it = m_managers.find(std::type_index(typeid(T)));
	if (it == m_managers.end()) {
		return nullptr;
	}

	return std::dynamic_pointer_cast<T>(it->second);
}

template<typename T>
bool Core::has() const
{
	static_assert(std::is_base_of<BaseManager, T>(), "Core::has<T>: T must be derived from BaseManager");

	const auto it = m_managers.find(std::type_index(typeid(T)));
	return it != m_managers.end();
}
