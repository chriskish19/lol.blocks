#ifndef WIN32_GUI_LOGGING_HPP
#define WIN32_GUI_LOGGING_HPP

namespace win32gui {
	class WIN32_GUI_API logging : public errors{
	public:
		logging() = default;

		logging(HWND parent_window) noexcept;
	private:
		std::wstring get_last_Error_win32() noexcept;

		win32gui::win32gui_error_codes send_to_log_window() noexcept;

		log_window m_window;
	};
}

// WIN32_GUI_LOGGING_HPP
#endif