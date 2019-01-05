#pragma once

#include <cstdint>
#include <string>

namespace tms {

typedef uint8_t CharUtf8;
typedef uint16_t CharUtf16;
typedef uint32_t CharUtf32;

typedef std::basic_string<uint8_t> StringUtf8;
typedef std::basic_string<uint16_t> StringUtf16;
typedef std::basic_string<uint32_t> StringUtf32;

class UnicodeConverter
{
public:
	static StringUtf16::iterator utf8ToUtf16(StringUtf8::iterator beginIn, StringUtf8::iterator endIn, StringUtf16::iterator beginOut);
};

typedef UnicodeConverter uc;
}