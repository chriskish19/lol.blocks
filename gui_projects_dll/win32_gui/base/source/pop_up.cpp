#include "base/header/pop_up.hpp"

LRESULT win32gui::pop_up_window::ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);

        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case static_cast<int>(win32gui::pop_up_window::pop_up_window_menu::ID_POP_UP_WINDOW_OK):
        {
            
            break;
        }

        } // end of switch (LOWORD(wParam))
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

win32gui::win32gui_error_codes win32gui::pop_up_window::create_pop_up_window() noexcept{
    m_base_window_handle = CreateWindowEx(
        0,                                          // optional window styles
        m_c_name.c_str(),                           // class name
        m_title.c_str(),                            // window title
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,    // window style
        CW_USEDEFAULT, CW_USEDEFAULT,               // position
        200, 150,                                   // size
        NULL,                                       // parent window
        NULL,                                       // menu
        m_hinst,                                    // instance handle
        NULL                                        // app data
    );

    m_OK_BUTTON = CreateWindowEx(
        0,                                                          // optional window styles
        L"BUTTON",                                                  // class name
        m_title.c_str(),                                            // window title
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,      // window style
        CW_USEDEFAULT, CW_USEDEFAULT,               // position
        50, 50,                                     // size
        m_base_window_handle,                       // parent window
        NULL,                                       // menu
        m_hinst,                                    // instance handle
        NULL                                        // app data
    );

    ShowWindow(m_base_window_handle, SW_SHOW);
}


win32gui::pop_up_window::pop_up_window(std::wstring& const title) noexcept
    :m_title(title)
{
    create_pop_up_window();
}


