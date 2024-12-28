#ifndef WIN32_GUI_LOGGING_HPP
#define WIN32_GUI_LOGGING_HPP

// dll macro import/export
#include "win32gui_macro_import.hpp"

// c++ stl
#include "win32gui_stl.hpp"

// windows win32 includes
#include "win32_header_includes.hpp"

// class include dependants
#include "errors.hpp"  // log_window and window_base use error_codes
#include "ground.hpp"  // log_window inherits window_base
#include "log_window.hpp"


namespace win32gui {
	class logging : public errors,public log_window{
	public:
		logging() = default;
		logging(HWND parent_window) noexcept;
	protected:
		std::wstring get_last_Error_win32() noexcept;

		win32gui::win32gui_error_codes send_to_log_window() noexcept;
	};
}

// WIN32_GUI_LOGGING_HPP
#endif