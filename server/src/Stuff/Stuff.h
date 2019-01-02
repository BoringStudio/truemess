#pragma once

#include <memory>
#include <string>

namespace detail
{
	template<typename T>
	class TypenameGetter
	{
	public:
		static std::string get()
		{
			static std::string name = getTypename();
			return name;
		}

	private:
		static constexpr std::string getTypename()
		{
			constexpr auto frontSize = sizeof("detail::TypenameGetter<") - 1;
			constexpr auto endSize = sizeof(">::getTypename") - 1;

			return std::string(__FUNCTION__ + frontSize, sizeof(__FUNCTION__) - frontSize - endSize - 1);
		}
	};

	template<typename T>
	class PointerDefs
	{
	public:
		using ptr = std::shared_ptr<T>;
		using uptr = std::unique_ptr<T>;
	};
}