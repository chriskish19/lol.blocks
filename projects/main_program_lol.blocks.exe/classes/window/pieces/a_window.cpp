#include "a_window.hpp"

window::a_window::a_window(const string& title)
	:m_title(title)
{

}

UINT window::a_window::width()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {

#if ENABLE_ALL_EXCEPTIONS
        throw errors::get_client_rect_failed();
#endif
        errors::handle_error_codes(errors::codes::get_client_rect_failed);
    }

    return rc.right - rc.left;
}

UINT window::a_window::height()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {

#if ENABLE_ALL_EXCEPTIONS
        throw errors::get_client_rect_failed();
#endif
        errors::handle_error_codes(errors::codes::get_client_rect_failed);
    }

    return rc.bottom - rc.top;
}
