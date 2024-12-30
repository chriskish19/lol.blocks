// class definition header
#include "log_window.hpp"


win32gui::log_window::log_window(const std::wstring& title) noexcept
    :m_title(title)
{
    m_message_pumper_thread = new std::thread(&win32gui::log_window::launch_log_window, this);
    
    m_windows_strings.add(L"Hello!");
    m_hello = m_windows_strings.get_data();

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
    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(win32gui::log_window::log_window_menu::ID_TOGGLE_TEXT), L"&Show Text");
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
  
        EndPaint(hwnd, &ps);

        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case static_cast<int>(win32gui::log_window::log_window_menu::ID_LOG_WINDOW_FILE_EXIT): // menu button called "FILE"
        {

            break;
        }
        case static_cast<int>(win32gui::log_window::log_window_menu::ID_TOGGLE_TEXT): {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (m_show_text) {
                // All painting occurs here, between BeginPaint and EndPaint.
                TextOut(hdc, 10, 20, m_hello.m_windows_string, m_hello.m_length);
                m_show_text = false;
            }
            else {
                TextOut(hdc, 10, 20, L"", 0);
                m_show_text = true;
            }
            

            
            EndPaint(hwnd, &ps);
            
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
    // InvalidateRect(m_base_window_handle, NULL, TRUE); // Force window redraw

    return win32gui_error_codes::success;
}

win32gui::win32gui_error_codes win32gui::log_window::launchy_thread_message_pumper() noexcept
{
    message_pumper();
    return win32gui::win32gui_error_codes::success;
}

void win32gui::log_window::message_pumper() noexcept
{
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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

