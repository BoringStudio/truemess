#pragma once

#include "../Core/Core.h"

template<class T>
class Manager : public BaseManager, public detail::PointerDefs<T>
{
public:
	Manager(const Core& core) : BaseManager(core) {}
	virtual ~Manager() = default;

	template<typename... Args>
	void log(Args&&... args);
};

template<class T>
template<typename ... Args>
void Manager<T>::log(Args&&... args)
{
	getCore().print<T>(std::forward<Args>(args)...);
}
