// class include
#include "errors.hpp"

win32gui::errors::errors(std::initializer_list<win32gui_error_codes> codes) noexcept
{
	for (auto code : codes) {
		m_public_codes_vec.push_back(code);
	}
}