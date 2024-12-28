#pragma once

// dll macro import/export
#include "win32gui_macro_import.hpp"

// c++ stl
#include "win32gui_stl.hpp"

// windows win32 includes
#include "win32_header_includes.hpp"

// class include dependants
#include "errors.hpp"  // log_window and window_base use error_codes


namespace win32gui {

	// a console like experiance for viewing log messages
	// but uses a win32 window 
	class log_window {
	public:
		log_window() = default;

		// constructor to create a logging window
		log_window(const std::wstring& title, HWND parent) noexcept;
		
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	protected:
		LRESULT CALLBACK ClassWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		HWND m_base_window_handle = nullptr;
		WNDCLASS m_wc = {};
		HINSTANCE m_hinst = GetModuleHandle(NULL);
		std::wstring m_c_name = L"logging window class";
		std::wstring m_title;
		void window_base_settings() noexcept;
		win32gui_error_codes create_log_window_menu() noexcept;

		enum class log_window_menu {
			ID_LOG_WINDOW_FILE_EXIT,
			ID_LOG_WINDOW_HELP_ABOUT
		};

		win32gui_error_codes add_display_message_in_window(const std::wstring& message) noexcept;

		
		int m_scroll_position = 0;
	};
}
