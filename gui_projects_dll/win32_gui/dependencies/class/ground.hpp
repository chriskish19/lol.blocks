#ifndef WIN32_GUI_GROUND_HPP
#define WIN32_GUI_GROUND_HPP

// cookie cutter windows

namespace win32gui {
	class window_base {
	public:
		window_base() {
			window_base_settings();
		};

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept {
            // reroute to protected window proc
            window_base* p_window_rerouter = nullptr;

            if (uMsg == WM_NCCREATE)
            {
                // Store the pointer to the window instance in the user data associated with the HWND.
                CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
                p_window_rerouter = (window_base*)pCreate->lpCreateParams;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
            }
            else
            {
                // Retrieve the pointer to the window instance from the user data associated with the HWND.
                p_window_rerouter = (window_base*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            }

            if (p_window_rerouter)
            {
                return p_window_rerouter->ProtectedWindowProc(hwnd, uMsg, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }

		};

	protected:
		virtual LRESULT CALLBACK ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept = 0;

		HWND m_base_window_handle = nullptr;
		WNDCLASS m_wc = {};
		HINSTANCE m_hinst = GetModuleHandle(NULL);
		std::wstring m_c_name = L"window_base";

        void window_base_settings() noexcept {
            m_wc.lpfnWndProc = WindowProc;
            m_wc.hInstance = m_hinst;
            m_wc.lpszClassName = m_c_name.c_str();

            RegisterClass(&m_wc);
        };
	};
	
}



// WIN32_GUI_GROUND_HPP
#endif