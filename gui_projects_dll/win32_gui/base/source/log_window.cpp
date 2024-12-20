#include "base/header/log_window.hpp"

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
        LoadMenu(m_hinst, MAKEINTRESOURCE(WIN32GUI_IDR_MENU1)),  // Load the menu here
        m_hinst,                                                // Instance handle
        this                                                    // Additional application data
    );

    ShowWindow(m_base_window_handle, SW_SHOW);
}

