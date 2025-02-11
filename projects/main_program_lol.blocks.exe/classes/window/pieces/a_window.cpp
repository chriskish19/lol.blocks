#include "a_window.hpp"

window::a_window::a_window(const string& title)
{
    m_title = title;
}

UINT window::a_window::width()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {
#if ENABLE_ALL_EXCEPTIONS
        win32_code_objs::code_obj error(win32_code_objs::get_client_rect_fail);
        throw errors::get_client_rect_failed(error);
#endif
        errors::handle_win32_error_codes(errors::win32_codes::get_client_rect_fail);
    }

    return rc.right - rc.left;
}

UINT window::a_window::height()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {

#if ENABLE_ALL_EXCEPTIONS
        win32_code_objs::code_obj error(win32_code_objs::get_client_rect_fail);
        throw errors::get_client_rect_failed(error);
#endif
        errors::handle_win32_error_codes(errors::win32_codes::get_client_rect_fail);
    }

    return rc.bottom - rc.top;
}
