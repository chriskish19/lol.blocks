#ifndef WIN32_GUI_LOG_WINDOW_HPP
#define WIN32_GUI_LOG_WINDOW_HPP

#include "dependencies/include/header/win32gui_dependencies_include.hpp"


namespace win32gui {
	class WIN32_GUI_API log_window :public window_base {
	public:
		enum class log_window_styles {
			basic = WS_CHILD,
			fancy = WS_OVERLAPPEDWINDOW,
			pop = WS_POPUP
		};



		log_window() = default;

		HWND create();

		HWND get_handle() { return log_window_handle; }
	protected:
		HWND log_window_handle = nullptr;

		unsigned int xPos = 0;
		unsigned int yPos = 0;

		void log_window_settings();
	};
}



// WIN32_GUI_LOG_WINDOW
#endif