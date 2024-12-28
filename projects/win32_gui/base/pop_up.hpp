#ifndef WIN32_GUI_POP_UP_HPP
#define WIN32_GUI_POP_UP_HPP

// dll macro import/export
#include "win32gui_macro_import.hpp"

// c++ stl
#include "win32gui_stl.hpp"

// windows win32 includes
#include "win32_header_includes.hpp"

// class dependents
#include "errors.hpp"
#include "ground.hpp"

namespace win32gui {
	class pop_up_window : public window_base {
	public:
		pop_up_window() noexcept;

		pop_up_window(const std::wstring& title) noexcept;

		LRESULT CALLBACK ClassWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;
	protected:
		

		win32gui_error_codes create_pop_up_window() noexcept;

		std::wstring m_title = L"WARNING POPUP WINDOW";

		HWND m_OK_BUTTON = nullptr;

		enum class pop_up_window_menu {
			ID_POP_UP_WINDOW_OK
		};
	};
}

// WIN32_GUI_POP_UP
#endif