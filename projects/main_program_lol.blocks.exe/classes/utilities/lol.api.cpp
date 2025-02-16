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
    
    /*
    * 
    Converts a sequence of wide characters from the array whose first element is pointed to by *src 
    to its narrow multibyte representation that begins in the conversion state described by *ps. 
    If dst is not null, converted characters are stored in the successive elements of the char array 
    pointed to by dst. No more than len bytes are written to the destination array. 


    std::size_t wcsrtombs( char* dst,
                       const wchar_t** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to narrow character array where the multibyte characters will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated wide string
    len 	- 	number of bytes available in the array pointed to by dst
    ps 	    - 	pointer to the conversion state object

    */
    
    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &wide, 0, nullptr);

    // if length is greater than max_string_buffer, we have an error:
    // throw an exception
    // send an error message to a popup window
    // return an empty string
    if (length > max_string_buffer) {
#if ENABLE_ALL_EXCEPTIONS
        {
            code_error_objs::code_obj error(code_error_objs::string_length_too_long);
            throw errors::string_length_too_long(error, wide);
        }
// ENABLE_ALL_EXCEPTIONS
#endif 

#if ENABLE_ERROR_OUTPUT_WINDOW
        {
            code_error_objs::code_obj error(code_error_objs::string_length_too_long);
            errors::string_length_too_long w32err(error, wide);
            errors::show_error_message_window(w32err.full_error_message());
        }
// ENABLE_ERROR_OUTPUT_WINDOW
#endif
        // return an empty string
        return {};
    }

    // stack buffer
    char buffer[max_string_buffer];
    
    // according to documentation:
    /*
    
    The following functions should not be called from multiple threads without synchronization with 
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.
    
    */
    std::size_t error_code = std::wcsrtombs(buffer,&wide,length,nullptr);
    

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
#if ENABLE_ALL_EXCEPTIONS
        {
            code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
            throw errors::to_narrow_string_fail(error);
        }
// ENABLE_ALL_EXCEPTIONS
#endif 

#if ENABLE_ERROR_OUTPUT_WINDOW
        {
            code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
            errors::to_narrow_string_fail w32err(error);
            errors::show_error_message_window(w32err.full_error_message());
        }
// ENABLE_ERROR_OUTPUT_WINDOW
#endif 
        // returns an empty string
        return {};
    }
    
    // return the narrow string using the stack buffer
    return std::string(buffer);
}

std::string utilities::to_narrow_string(const std::wstring& wide)
{
    // get the length of the wide string, not including '\0'
    size_t length = wide.length();

    // if length is greater than "max_string_buffer" , an error has occurred:
    // throw an exception
    // output the error to a popup window
    // return empty string
    if (length > max_string_buffer) {
#if ENABLE_ALL_EXCEPTIONS
        {
            code_error_objs::code_obj error(code_error_objs::string_length_too_long);
            throw errors::string_length_too_long(error,wide);
        }
// ENABLE_ALL_EXCEPTIONS
#endif 

#if ENABLE_ERROR_OUTPUT_WINDOW
        {
            code_error_objs::code_obj error(code_error_objs::string_length_too_long);
            errors::string_length_too_long w32err(error,wide);
            errors::show_error_message_window(w32err.full_error_message());
        }
// ENABLE_ERROR_OUTPUT_WINDOW
#endif
        // return an empty string
        return {};
    }

    // stack buffer
    char buffer[max_string_buffer];

    if (std::wcstombs(buffer, wide.c_str(), length) == (size_t)-1) {
#if ENABLE_ALL_EXCEPTIONS
        {
            code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
            throw errors::to_narrow_string_fail(error);
        }
// ENABLE_ALL_EXCEPTIONS
#endif 

#if ENABLE_ERROR_OUTPUT_WINDOW
        {
            code_error_objs::code_obj error(code_error_objs::to_narrow_string_failed);
            errors::to_narrow_string_fail w32err(error);
            errors::show_error_message_window(w32err.full_error_message());
        }
// ENABLE_ERROR_OUTPUT_WINDOW
#endif 
        // returns an empty string
        return {};
    }
    
    // returns the narrow string
    return std::string(buffer);
}

std::wstring utilities::to_wide_string(const char* narrow, errors::codes* code_p)
{
    
    
    
    return std::wstring();
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
