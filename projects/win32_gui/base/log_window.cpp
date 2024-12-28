// class definition header
#include "log_window.hpp"


win32gui::log_window::log_window(const std::wstring& title,HWND parent) noexcept
    :m_title(title)
{
    window_base_settings();

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

    if (m_base_window_handle == nullptr) {
        throw;
    }
    
    
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

LRESULT win32gui::log_window::ClassWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
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
        break;
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
        
        LPWSTR message = new WCHAR[]{ L"Hello" };
        TextOut(hdc, 10, 20, message, 6);

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
        si.nPos = std::max(0, std::min(si.nPos, 100)); 
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

win32gui::win32gui_error_codes win32gui::log_window::add_display_message_in_window(const std::wstring& message) noexcept
{
    //m_all_log_messages_vec.push_back(message); 
    InvalidateRect(m_base_window_handle, NULL, TRUE); // Force window redraw

    return win32gui_error_codes::success;
}

void win32gui::log_window::window_base_settings() noexcept
{
    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hinst;
    m_wc.lpszClassName = m_c_name.c_str();

    RegisterClass(&m_wc);
}

LRESULT CALLBACK win32gui::log_window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    // reroute to protected window proc
    win32gui::log_window* p_window_rerouter = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Store the pointer to the window instance in the user data associated with the HWND.
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_window_rerouter = (log_window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
    }
    else
    {
        // Retrieve the pointer to the window instance from the user data associated with the HWND.
        p_window_rerouter = (log_window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (p_window_rerouter)
    {
        return p_window_rerouter->ClassWindowProc(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

