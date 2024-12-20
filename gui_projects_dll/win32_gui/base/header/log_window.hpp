#ifndef WIN32_GUI_LOG_WINDOW_HPP
#define WIN32_GUI_LOG_WINDOW_HPP

#include "dependencies/include/header/win32gui_dependencies_include.hpp"

namespace win32gui {
	class WIN32_GUI_API log_window :public window_base {
	public:
		log_window() = default;
		log_window(std::wstring const& title, HWND parent) noexcept;
		create_menu()
	protected:
		std::wstring m_title = L"logging window";
	};
}



// WIN32_GUI_LOG_WINDOW
#endif