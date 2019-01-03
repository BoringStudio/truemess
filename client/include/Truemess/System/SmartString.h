#pragma once

#include <cstdint>
#include <string>

namespace tms {
class SmartString
{
public:
	typedef std::basic_string<uint32_t>::iterator Iterator;

	SmartString(const std::string& str);

private:
	/**
	 * \brief SmartString content. It is utf32 string
	 */
	std::basic_string<uint32_t> m_string;
};
}