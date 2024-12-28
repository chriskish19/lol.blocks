#pragma once
#include <windows.h>

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

#include "stl_macro_definitions.hpp"


class windows_types {
public:

	void add(wchar_t c) {
		m_windows_types_container.emplace();
	}
private:
	std::any m_windows_types_container;

};
