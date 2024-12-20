#ifndef WIN32_GUI_LOG_WINDOW_HPP
#define WIN32_GUI_LOG_WINDOW_HPP

#include "dependencies/include/header/win32gui_dependencies_include.hpp"

namespace win32gui {
	class WIN32_GUI_API log_window :public window_base {
	public:
		log_window() = default;
		log_window(std::wstring const& title, HWND parent) noexcept;
		
	protected:
		std::wstring m_title = L"logging window";

		win32gui_error_codes create_log_window_menu() noexcept;

		LRESULT CALLBACK ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;

		enum class log_window_menu {
			ID_LOG_WINDOW_FILE_EXIT,
			ID_LOG_WINDOW_HELP_ABOUT
		};
	};
}


// WIN32_GUI_LOG_WINDOW
#endif