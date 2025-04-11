/***********************************************
* File: lol_window.hpp
*
* Purpose: win32 window creation
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH

namespace lol_blocks {
	
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


	HWND create_window(const window_description& wd);

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

	codes register_window(const WNDCLASSEX& wc);


	// standard window procedure
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// custom window procedures here...
	LRESULT CALLBACK main_window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}