#include "system_log_window.hpp"

errors::codes window::system_log_window::go()
{
    set_font(m_font_size);
    window_settings();
    create_window();
    remove_x_log_window();
    m_scroll_p->set_scroll_info(m_window_handle);
    message_pump();
	return errors::codes::success;
}

void window::system_log_window::window_settings()
{
    m_slw_wc.lpfnWndProc = WindowProc;
    m_slw_wc.hInstance = m_hinst;
    m_slw_wc.lpszClassName = READ_ONLY_STRING("system log window");

    ATOM atm = RegisterClass(&m_slw_wc);

#if ENABLE_FULL_DEBUG
    if (atm == FALSE) {
        errors::handle_error_codes(errors::codes::win32_register_class_fail);
    }
#endif

#if ENABLE_ALL_EXCEPTIONS
    if (atm == FALSE) {
        throw errors::win32_register_class_fail();
    }
#endif
}

void window::system_log_window::create_window()
{
    m_window_handle = CreateWindowEx(
        0,                                                  // Optional window styles.
        m_slw_class_name.c_str(),                           // Window class
        m_slw_title.c_str(),                                // Window text
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,                   // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                                           // Parent window    
        NULL,                                           // Load the menu here
        m_hinst,                                        // Instance handle
        this                                            // Additional application data
    );

#if ENABLE_ALL_EXCEPTIONS
    if (m_window_handle == nullptr) {
        throw errors::win32_HWND_error();
    }
#endif

#if ENABLE_FULL_DEBUG
    if (m_window_handle == nullptr) {
        errors::handle_error_codes(errors::codes::win32_HWND_error);
    }
#endif

    ShowWindow(m_window_handle, SW_SHOW);
}
