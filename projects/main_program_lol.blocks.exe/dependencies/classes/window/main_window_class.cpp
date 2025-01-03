// class include
#include "main_window_class.hpp"

main_lol_blocks_exe::window_manager::~window_manager() {
    
}

LRESULT main_lol_blocks_exe::window_relative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    // reroute to private window proc
    window_relative* p_window_rerouter = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Store the pointer to the window instance in the user data associated with the HWND.
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_window_rerouter = (window_relative*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
    }
    else
    {
        // Retrieve the pointer to the window instance from the user data associated with the HWND.
        p_window_rerouter = (window_relative*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (p_window_rerouter)
    {
        return p_window_rerouter->PrivateWindowProc(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT main_lol_blocks_exe::window_relative::PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
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
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case static_cast<int>(main_window_menu_ids::Create): // menu button called "Create New Window"
        {
            // signal to window_class_mt to create a new thread window
            global_new_window_gate_latch_p->store(true);
            global_window_create_signaler_p->notify_all();
            break;
        }

        } // end of switch (LOWORD(wParam))
        break;
    }
    case WM_CLOSE: {
        // signal to window_class_mt to kill the thread??
        break;
    }
    
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

main_lol_blocks_exe::window_relative::window_relative(const std::wstring& title) noexcept
:m_title(title) 
{
    if (m_is_class_registered == false) {
        this->register_class();
        m_is_class_registered = true;
    }
    
    m_window_handle = CreateWindowEx(
        0,                                  // Optional window styles.
        m_c_name.c_str(),                     // Window class
        m_title.c_str(),                      // Window text
        WS_OVERLAPPEDWINDOW,                // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                                           // Parent window    
        NULL,                                           // Load the menu here
        m_hinst,                                          // Instance handle
        this // Additional application data
    );

    ShowWindow(m_window_handle, SW_SHOW);

    this->build_relative_window_menu_bar();
}

main_lol_blocks_exe::window_relative::~window_relative()
{
   
}

void main_lol_blocks_exe::window_relative::change_title(const std::wstring& new_title) noexcept
{
    SetWindowText(this->m_window_handle, new_title.c_str());
}

utilities::lolblock_ec::codes main_lol_blocks_exe::window_relative::build_relative_window_menu_bar() noexcept
{
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();
    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(main_window_menu_ids::File), L"&File");
    AppendMenu(hHelpMenu, MF_STRING, static_cast<int>(main_window_menu_ids::Help), L"&Help");
    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(main_window_menu_ids::Create), L"&Create New Window");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help");
    SetMenu(this->m_window_handle, hMenu);

    // reaches end without crashing it means success??
    return utilities::lolblock_ec::codes::success;
}
