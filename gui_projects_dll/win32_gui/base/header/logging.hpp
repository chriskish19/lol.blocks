#ifndef WIN32_GUI_LOGGING_HPP
#define WIN32_GUI_LOGGING_HPP

#include "dependencies/include/header/win32gui_dependencies_include.hpp"

namespace win32gui {
	class WIN32_GUI_API logging : public errors, public log_window{
	public:
		logging() = default;

		logging(std::initializer_list<win32gui::win32gui_error_codes> codes) noexcept;

		logging(std::wstring const& error_message) noexcept;


	private:
		std::wstring get_last_Error_win32() noexcept;

		win32gui::win32gui_error_codes send_to_log_window() noexcept;
	};
}



// WIN32_GUI_LOGGING_HPP
#endif