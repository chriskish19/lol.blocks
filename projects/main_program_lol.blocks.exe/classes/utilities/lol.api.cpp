#include "lol.api.hpp"
#include "lol.api.hpp"

errors::codes utilities::win32_menu_check(HMENU p_menu,const string& location)
{
    if (p_menu == nullptr) {

        errors::win32_menu_error w32err(location);
        errors::show_error_message_window(w32err.full_error_message(), w32err.get_code_string());

#if ENABLE_ALL_EXCEPTIONS

        throw errors::win32_menu_error(location);

#endif // ENABLE_ALL_EXCEPTIONS

        return errors::codes::win32_menu_error;
    }
	
	return errors::codes::success;
}

errors::codes utilities::win32_append_menu_check(BOOL code, const string& location)
{
    if (code == FALSE) {
        errors::win32_menu_error w32err(location);
        errors::show_error_message_window(w32err.full_error_message(), w32err.get_code_string());
    
#if ENABLE_ALL_EXCEPTIONS

        throw errors::win32_menu_error(location);

#endif // ENABLE_ALL_EXCEPTIONS

        return errors::codes::win32_menu_error;
    }
    return errors::codes::success;
}
