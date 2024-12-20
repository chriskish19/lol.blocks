#include "base/header/log_window.hpp"

// TODO: add basic error handling



win32gui::log_window::log_window(std::wstring const& title,HWND parent) noexcept
    :m_title(title)
{
    m_base_window_handle = CreateWindowEx(
        0,                              // Optional window styles.
        m_c_name.c_str(),               // Window class
        m_title.c_str(),                // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        parent,                                                 // Parent window    
        NULL,                                                   // Load the menu here
        m_hinst,                                                // Instance handle
        this                                                    // Additional application data
    );

    if (create_log_window_menu() != win32gui_error_codes::success) {
        MessageBox(m_base_window_handle, L"Menu failed to be created...??", L" error Info", MB_OK);
    }

    ShowWindow(m_base_window_handle, SW_SHOW);
}

win32gui::win32gui_error_codes win32gui::log_window::create_log_window_menu() noexcept
{
    HMENU hMenu = CreateMenu(); 
    HMENU hFileMenu = CreateMenu(); 
    HMENU hHelpMenu = CreateMenu(); 
    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(win32gui::log_window::log_window_menu::ID_LOG_WINDOW_FILE_EXIT), L"&Exit");
    AppendMenu(hHelpMenu, MF_STRING, static_cast<int>(win32gui::log_window::log_window_menu::ID_LOG_WINDOW_HELP_ABOUT), L"&About");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File"); 
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help"); 
    SetMenu(m_base_window_handle, hMenu);

    // reaches end without crashing it means success??
    return win32gui_error_codes::success;
}

LRESULT win32gui::log_window::ProtectedWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
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
        case static_cast<int>(win32gui::log_window_menu::ID_LOG_WINDOW_FILE_EXIT): // menu button called "FILE"
        {

            break;
        }

        } // end of switch (LOWORD(wParam))
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

