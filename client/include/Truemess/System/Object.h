#pragma once

#include <cstdint>

namespace tms {
class Object
{
public:
	Object();

	virtual ~Object() = default;

	uint32_t id() const;

	static uint32_t nextID();

private:
	const uint32_t m_ID;
};
}