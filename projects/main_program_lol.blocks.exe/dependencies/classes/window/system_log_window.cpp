#include "system_log_window.hpp"

errors::codes window::system_log_window::go()
{
    set_font(m_font_size);
    window_settings();
    create_window();
    remove_x_log_window();
    SetWindowText(m_window_handle, READ_ONLY_STRING("SYSTEM LOG WINDOW"));
    m_scroll_p->set_scroll_info(m_window_handle);
    message_pump();
	return errors::codes::success;
}
