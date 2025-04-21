#include NAMES_INCLUDE
#include WINDOW_INCLUDE_PATH


LRESULT CALLBACK lol_blocks::main_window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
	
	switch (message) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add your painting code here
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			int wmEvent = HIWORD(wParam);
			// TODO: Handle menus, buttons, etc. here
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


HWND lol_blocks::create_window(const window_description& wd) {

	/*
	
	HWND CreateWindowExW(
		  [in]           DWORD     dwExStyle,
		  [in, optional] LPCWSTR   lpClassName,
		  [in, optional] LPCWSTR   lpWindowName,
		  [in]           DWORD     dwStyle,
		  [in]           int       X,
		  [in]           int       Y,
		  [in]           int       nWidth,
		  [in]           int       nHeight,
		  [in, optional] HWND      hWndParent,
		  [in, optional] HMENU     hMenu,
		  [in, optional] HINSTANCE hInstance,
		  [in, optional] LPVOID    lpParam
		);
	
	*/

	return CreateWindowEx(
		wd.dwExStyle,
		wd.lpClassName,
		wd.lpWindowName,
		wd.dwStyle,
		wd.X,
		wd.Y,
		wd.nWidth,
		wd.nHeight,
		wd.hWndParent,
		wd.hMenu,
		wd.hInstance,
		wd.lpParam
	);
}

lol_blocks::codes lol_blocks::register_window(const WNDCLASSEX& wc) {
	ATOM atm = RegisterClassEx(&wc);

	if (atm == 0) {
		return codes::register_class_fail;
	}

	return codes::success;
}

LRESULT CALLBACK lol_blocks::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add your painting code here
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			int wmEvent = HIWORD(wParam);
			// TODO: Handle menus, buttons, etc. here
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
