#ifndef WIN32GUI_ERROR_HANDLING_HPP
#define WIN32GUI_ERROR_HANDLING_HPP

// dll macro import/export
#include "win32gui_macro_import.hpp"

// c++ stl
#include "win32gui_stl.hpp"

// windows win32 includes
#include "win32_header_includes.hpp"

namespace win32gui {
	enum class win32gui_error_codes {
		success = 0,
		window_create_fail,
		hwnd_nullptr

	};
	
	
	class errors {
	public:
		errors() = default;

		errors(std::initializer_list<win32gui_error_codes> codes) noexcept;

		std::vector<win32gui_error_codes> m_public_codes_vec = {};

		std::unordered_map<win32gui_error_codes, std::wstring> m_error_codes_mp =
		{
			{win32gui_error_codes::hwnd_nullptr,L"handle to window is nullptr, something went wrong with win32 api" },
			{win32gui_error_codes::window_create_fail,L"failed to create window when using win32 api"},
			{}
		};
	};
}

// WIN32GUI_ERROR_HANDLING_HPP
#endif