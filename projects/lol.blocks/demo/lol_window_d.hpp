/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include WINDOW_INCLUDE_PATH


namespace lol_blocks {
	class main_window {
	public:
		main_window();

		HWND handle() { return m_handle; }

		std::vector<codes> get_codes();
	protected:
		codes m_hwnd_code = codes::uninitialized;
		codes m_register_code = codes::uninitialized;


		HWND m_handle;

		/*
		
		struct window_description {
				DWORD			dwExStyle;    // The extended window style of the window being created
				w32_str_cp		lpClassName;  // The class name of the window
				w32_str_cp		lpWindowName; // The name/title of the window
				DWORD			dwStyle;      // The style of the window
				int				X;            // The initial horizontal position of the window
				int				Y;            // The initial vertical position of the window
				int				nWidth;       // The width of the window
				int				nHeight;      // The height of the window
				HWND			hWndParent;   // Handle to the parent or owner window
				HMENU			hMenu;        // Handle to a menu, or child-window identifier
				HINSTANCE		hInstance;    // Handle to the instance of the module to be associated with the window
				LPVOID			lpParam;      // Pointer to additional application-defined data
			};
		
		*/

		window_description m_wd = {
			NULL,
			ROS("MainWindow"),
			ROS("lol.blocks"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		};

		/*

				typedef struct tagWNDCLASSEX {
			  UINT				cbSize;
			  UINT				style;
			  WNDPROC			lpfnWndProc;
			  int				cbClsExtra;
			  int				cbWndExtra;
			  HINSTANCE			hInstance;
			  HICON				hIcon;
			  HCURSOR			hCursor;
			  HBRUSH			hbrBackground;
			  w32_str_cp		lpszMenuName;
			  w32_str_cp		lpszClassName;
			  HICON				hIconSm;
					} WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;

	*/

		WNDCLASSEX m_wc = {
			sizeof(WNDCLASSEX),
			CS_HREDRAW | CS_VREDRAW,
			lol_blocks::main_window_proc,
			0,
			0,
			GetModuleHandle(NULL),
			LoadIcon(nullptr, IDI_APPLICATION),
			LoadCursor(nullptr, IDC_ARROW),
			reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
			nullptr,
			ROS("MainWindow"),
			LoadIcon(nullptr, IDI_APPLICATION)
		};
	};
}