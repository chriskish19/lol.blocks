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
	

	
private:
	std::vector<std::any> m_windows_types_container;

	
};

class windows_string {
public:
	struct long_p_const_wide_string_windows {
		long_p_const_wide_string_windows() = default;

		long_p_const_wide_string_windows(LPCWSTR the_string, size_t the_length) noexcept
			:m_windows_string(the_string), m_length(the_length) {
		}

		LPCWSTR m_windows_string = nullptr;
		size_t m_length = 0ull;
	};

	void reset() noexcept {
		m_windows_wide_strings = std::vector<std::vector<wchar_t>>();
	}

	void add(const std::vector<wchar_t>& c_wide_vec) noexcept {
		m_windows_wide_strings.push_back(c_wide_vec);
	}

	void add(const std::wstring& w_str) noexcept {
		std::vector<wchar_t> w_char_vec = {};
		for (auto c : w_str) {
			w_char_vec.push_back(c);
		}
		m_windows_wide_strings.push_back(w_char_vec);
	}

	long_p_const_wide_string_windows get_data(unsigned int i = 0) noexcept {
		auto window_string_p = m_windows_wide_strings.at(i).data();
		auto length = m_windows_wide_strings.at(i).size();
		return { window_string_p, length };
	}


private:

	std::vector<std::vector<wchar_t>> m_windows_wide_strings;
};
