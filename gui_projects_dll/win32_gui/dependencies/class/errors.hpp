#ifndef WIN32GUI_ERROR_HANDLING_HPP
#define WIN32GUI_ERROR_HANDLING_HPP

namespace win32gui {
	enum class WIN32_GUI_API win32gui_error_codes {
		success = 0,
		window_create_fail,
		hwnd_nullptr

	};
	
	std::unordered_map<win32gui_error_codes, std::wstring> win32gui_global_map_error_codes =
	{
		{win32gui_error_codes::hwnd_nullptr,L"handle to window is nullptr, something went wrong with win32 api" },
		{win32gui_error_codes::window_create_fail,L"failed to create window when using win32 api"},
		{}
	};

	class WIN32_GUI_API errors {
	public:
		errors(std::initializer_list<win32gui_error_codes> codes) noexcept {
			for (auto code : codes) {
				m_codes_vec.push_back(code);
			}
		}

		void display_in_window(HWND log_window) noexcept {

		}


	private:
		std::vector<win32gui_error_codes> m_codes_vec = {};


	};
}





// WIN32GUI_ERROR_HANDLING_HPP
#endif