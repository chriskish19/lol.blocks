#ifndef WIN32_GUI_GROUND_HPP
#define WIN32_GUI_GROUND_HPP

// dll macro import/export
#include "win32gui_macro_import.hpp"

// c++ stl
#include "win32gui_stl.hpp"

// windows win32 includes
#include "win32_header_includes.hpp"

namespace win32gui {
	class window_base {
	public:
		window_base() = default;

		window_base(const std::wstring& title) noexcept;

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		virtual LRESULT CALLBACK ClassWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept = 0;
	
	protected:
		HWND m_base_window_handle = nullptr;
		WNDCLASS m_wm = {};
		HINSTANCE m_hinst = GetModuleHandle(NULL);
		std::wstring m_c_name = L"window_base";
		std::wstring m_title;
        void window_base_settings() noexcept;
	};
	
}

// WIN32_GUI_GROUND_HPP
#endif