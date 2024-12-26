#ifndef WIN32_GUI_LOGGING_HPP
#define WIN32_GUI_LOGGING_HPP

namespace win32gui {
	class WIN32_GUI_API logging : public errors,public log_window{
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