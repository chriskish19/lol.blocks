#pragma once
#include <windows.h>

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

#include "stl_macro_definitions.hpp"


class windows_string {
public:
	windows_string(const std::wstring& s) noexcept;
	LPCWSTR get_raw_p() noexcept { return m_lpcws; }
private:
	std::wstring m_ws;
	LPCWSTR m_lpcws;
};
