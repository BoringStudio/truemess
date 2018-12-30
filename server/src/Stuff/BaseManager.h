#pragma once

#include <memory>

class Core;

class BaseManager
{
public:
	explicit BaseManager(const Core& core);
	virtual ~BaseManager() = default;

	const Core& getCore() const;

private:
	const Core& m_core;
};

template<typename T>
class PointerDefs
{
public:
	using ptr = std::shared_ptr<T>;
	using uptr = std::unique_ptr<T>;
};