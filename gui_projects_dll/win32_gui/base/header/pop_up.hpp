#ifndef WIN32_GUI_POP_UP_HPP
#define WIN32_GUI_POP_UP_HPP


namespace win32gui {
	class WIN32_GUI_API pop_up_window : public window_base {
	public:
		pop_up_window() = default;
		pop_up_window() noexcept {
			create_pop_up_window();
		}
		pop_up_window(std::wstring& const title) noexcept;

	protected:
		LRESULT CALLBACK ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;

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