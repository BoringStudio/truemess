#pragma once

#include <cstdint>
#include <string>

namespace tms {

typedef std::basic_string<uint8_t> Utf8;
typedef std::basic_string<uint16_t> Utf16;
typedef std::basic_string<uint32_t> Utf32;

class UnicodeConverter
{
public:
	static Utf16::iterator utf8ToUtf16(Utf8::iterator beginIn, Utf8::iterator endIn, Utf16::iterator beginOut)
};

typedef UnicodeConverter uc;
}