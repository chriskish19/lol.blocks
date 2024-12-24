#ifndef WIN32_GUI_LOG_WINDOW_HPP
#define WIN32_GUI_LOG_WINDOW_HPP


namespace win32gui {

	// a console like experiance for viewing log messages
	// but uses a win32 window 
	class WIN32_GUI_API log_window :public window_base {
	public:
		log_window() = default;

		// constructor to create a logging window
		log_window(std::wstring const& title, HWND parent) noexcept;
		
	protected:
		std::wstring m_title = L"logging window";

		win32gui_error_codes create_log_window_menu() noexcept;

		LRESULT CALLBACK ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;

		enum class log_window_menu {
			ID_LOG_WINDOW_FILE_EXIT,
			ID_LOG_WINDOW_HELP_ABOUT
		};

		win32gui_error_codes add_display_message_in_window(std::wstring const& message) noexcept;

		std::vector<std::wstring> m_all_log_messages_vec = {};
		int m_scroll_position = 0;
	};
}


// WIN32_GUI_LOG_WINDOW
#endif