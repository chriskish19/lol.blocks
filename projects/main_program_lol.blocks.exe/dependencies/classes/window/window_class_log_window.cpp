#include "window_class_log_window.hpp"

window::window_class_log_window::window_class_log_window(const string& title)
    :m_window_title(title)
{

}

errors::codes window::window_class_log_window::go()
{
    set_font(m_font_size);
    window_settings();
    create_window();
    remove_x_log_window();
    SetWindowText(m_window_handle, m_window_title.c_str());
    m_scroll_p->set_scroll_info(m_window_handle);
	
	return errors::codes::success;
}

void window::window_class_log_window::create_window()
{
    m_window_handle = CreateWindowEx(
        0,                                      // Optional window styles.
        m_c_name.c_str(),                       // Window class
        m_title.c_str(),                        // Window text
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,       // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                                           // Parent window    
        NULL,                                           // Load the menu here
        m_hinst,                                        // Instance handle
        this                                            // Additional application data
    );

    ShowWindow(m_window_handle, SW_HIDE);
}
