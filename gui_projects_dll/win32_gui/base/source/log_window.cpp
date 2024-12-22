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
    case WM_CREATE: {
        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL; 
        si.nMin = 0; 
        si.nMax = 100; 
        si.nPage = 10; 
        si.nPos = 0; 
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

        this->add_display_message_in_window(L"welcome, this window will show errors and useful info about lol.blocks");
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        
        // Set text color and background mode 
        SetTextColor(hdc, RGB(0, 0, 0)); 
        SetBkMode(hdc, TRANSPARENT); 
        
        // Draw the log messages 
        int y = 10; 
        for (int i = m_scroll_position; i < m_all_log_messages_vec.size(); ++i) { 
            TextOut(hdc, 10, y, m_all_log_messages_vec[i].c_str(), m_all_log_messages_vec[i].length());
            y += 20; 
        }

        EndPaint(hwnd, &ps);

        break;
    }
    case WM_VSCROLL: {
        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_VERT, &si);

        // Update scroll position based on user input 
        switch (LOWORD(wParam)) {
        case SB_LINEUP:
            si.nPos -= 1;
            break;
        case SB_LINEDOWN:
            si.nPos += 1;
            break;
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break;
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break;
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break;
        }

        
        // Ensure scroll position is within valid range 
        si.nPos = std::max(0, std::min(si.nPos, (int)m_all_log_messages_vec.size() - 1)); 
        m_scroll_position = si.nPos; 
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE); 
        InvalidateRect(hwnd, NULL, TRUE); 
        
        return 0;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case static_cast<int>(win32gui::log_window::log_window_menu::ID_LOG_WINDOW_FILE_EXIT): // menu button called "FILE"
        {

            break;
        }

        } // end of switch (LOWORD(wParam))
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

win32gui::win32gui_error_codes win32gui::log_window::add_display_message_in_window(std::wstring const& message) noexcept
{
    m_all_log_messages_vec.push_back(message); 
    InvalidateRect(m_base_window_handle, NULL, TRUE); // Force window redraw
}

