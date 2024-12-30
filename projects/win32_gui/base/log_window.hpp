#pragma once

// windows types
#include "win_types/types.hpp"

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
		log_window(const std::wstring& title) noexcept;
		
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		void launch_log_window() noexcept {
			window_base_settings();

			m_base_window_handle = CreateWindowEx(
				0,                              // Optional window styles.
				m_c_name.c_str(),               // Window class
				m_title.c_str(),                // Window text
				WS_OVERLAPPEDWINDOW,            // Window style

				// Size and position
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

				NULL,                                                 // Parent window    
				NULL,                                                   // Load the menu here
				m_hinst,                                                // Instance handle
				this                                                    // Additional application data
			);

			this->launchy_thread_message_pumper();
		}

		win32gui::win32gui_error_codes launchy_thread_message_pumper() noexcept;

		void join_m_message_pumper_thread() noexcept { 
			if (m_message_pumper_thread->joinable()) {
				m_message_pumper_thread->join();
			}
		}
		void detach_m_message_pumper_thread() noexcept { 
			if (m_message_pumper_thread->joinable()) {
				m_message_pumper_thread->detach();
			}
		}
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
			ID_LOG_WINDOW_FILE_EXIT=3,
			ID_LOG_WINDOW_HELP_ABOUT,
			ID_TOGGLE_TEXT
		};

		win32gui_error_codes add_display_message_in_window(const std::wstring& message) noexcept;

		windows_string m_windows_strings;
		windows_string::long_p_const_wide_string_windows m_hello;

		int m_scroll_position = 0;

		bool m_show_text = false;

		
		void message_pumper() noexcept;
		std::thread* m_message_pumper_thread = nullptr;
	};
}
