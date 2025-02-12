#include "lol.api.hpp"


std::wstring utilities::to_wide_string(const char* narrow)
{
    size_t length = strlen(narrow);
    wchar_t buffer[max_string_buffer];

    if (std::mbstowcs(buffer, narrow, length) == (size_t)-1) {
#if ENABLE_ALL_EXCEPTIONS
        code_error_objs::code_obj error(code_error_objs::to_wide_string_failed);
        throw errors::to_wide_string_fail(error);
#endif

#if ENABLE_FULL_DEBUG
        errors::handle_basic_error_codes(errors::codes::to_wide_string_failed);
#endif
        return {};
    }
    
    return std::wstring(buffer);
}

std::wstring utilities::to_wide_string(const std::string& narrow)
{
    size_t length = narrow.length();
    wchar_t buffer[max_string_buffer];

    if (std::mbstowcs(buffer, narrow.c_str(), length) == (size_t)-1) {
#if ENABLE_ALL_EXCEPTIONS
        code_error_objs::code_obj error(code_error_objs::to_wide_string_failed);
        throw errors::to_wide_string_fail(error);
#endif

#if ENABLE_FULL_DEBUG
        errors::handle_basic_error_codes(errors::codes::to_wide_string_failed);
#endif
        return {};
    }
    
    return std::wstring(buffer);
}

std::string utilities::to_narrow_string(const wchar_t* wide)
{
    size_t length = wcslen(wide);
    char buffer[max_string_buffer];
    
    if (std::wcstombs(buffer, wide, length) == (size_t)-1) {
#if ENABLE_ALL_EXCEPTIONS
        code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
        throw errors::to_narrow_string_fail(error);
#endif

#if ENABLE_FULL_DEBUG
        errors::handle_basic_error_codes(errors::codes::to_narrow_string_failed);
#endif
        return {};
    }
    
    return std::string(buffer);
}

std::string utilities::to_narrow_string(const std::wstring& wide)
{
    size_t length = wide.length();
    char buffer[max_string_buffer];

    if (std::wcstombs(buffer, wide.c_str(), length) == (size_t)-1) {
#if ENABLE_ALL_EXCEPTIONS
        code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
        throw errors::to_narrow_string_fail(error);
#endif

#if ENABLE_FULL_DEBUG
        errors::handle_basic_error_codes(errors::codes::to_narrow_string_failed);
#endif
        return {};
    }
    
    return std::string(buffer);
}

errors::win32_codes utilities::win32_menu_check(HMENU p_menu,const string& location)
{
    if (p_menu == nullptr) {
        {
            win32_code_objs::code_obj error(win32_code_objs::menu_error);
            errors::win32_menu_error w32err(error, location);
            errors::show_error_message_window(w32err.full_error_message());
        }

#if ENABLE_ALL_EXCEPTIONS
        {
            win32_code_objs::code_obj error(win32_code_objs::menu_error);
            throw errors::win32_menu_error(error, location);
        }

#endif // ENABLE_ALL_EXCEPTIONS

        return errors::win32_codes::menu_error;
    }
	
	return errors::win32_codes::success;
}

errors::win32_codes utilities::win32_append_menu_check(BOOL code, const string& location)
{
    if (code == FALSE) {
        {
            win32_code_objs::code_obj error(win32_code_objs::menu_error);
            errors::win32_menu_error w32err(error, location);
            errors::show_error_message_window(w32err.full_error_message());
        }
    
#if ENABLE_ALL_EXCEPTIONS
        {
            win32_code_objs::code_obj error(win32_code_objs::menu_error);
            throw errors::win32_menu_error(error, location);
        }

#endif // ENABLE_ALL_EXCEPTIONS

        return errors::win32_codes::menu_error;
    }
    return errors::win32_codes::success;
}

errors::codes utilities::is_path_valid(const std::filesystem::path& path)
{
    
    
    return errors::codes();
}

errors::codes utilities::create_directories(const std::filesystem::path& path)
{
    
#if ENABLE_ALL_EXCEPTIONS
    try {
        std::filesystem::create_directories(path);
    }
    catch (const std::filesystem::filesystem_error& e) {
        
    }
#endif
    return errors::codes();
}
