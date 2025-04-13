#include NAMES_INCLUDE
#include CODE_UTILITIES_INCLUDE_PATH


void lol_blocks::output_code(lb::codes code) {
	switch (code) {
		case lb::codes::success:
		{
			return;
		}
			
		case lb::codes::pointer_is_nullptr:
		{
			output_window(pointer_is_nullptr_description);
			break;
		}

		case lb::codes::wide_string_copy_fail_wcs_cpy:
		{
			output_window(wide_string_copy_fail_wcs_cpy_description);
			break;
		}

		case lb::codes::strings_not_equal:
		{
			output_window(strings_not_equal_description);
			break;
		}

		case lb::codes::empty_string:
		{
			output_window(empty_string_description);
			break;
		}

		case lb::codes::string_length_too_long:
		{
			output_window(string_length_too_long_description);
			break;
		}

		case lb::codes::index_out_of_range:
		{
			output_window(index_out_of_range_description);
			break;
		}

		case lb::codes::division_by_zero:
		{
			output_window(division_by_zero_description);
			break;
		}

		case lb::codes::unknown_keyboard_key_in_system_message_handler:
		{
			output_window(unknown_keyboard_key_in_system_message_handler_description);
			break;
		}

		case lb::codes::unknown_mouse_button_in_system_message_handler:
		{
			output_window(unknown_mouse_button_in_system_message_handler_description);
			break;
		}

		case lb::codes::dx_error:
		{
			output_window(dx_error_description);
			break;
		}

		case lb::codes::exception_thrown_and_handled:
		{
			output_window(exception_thrown_and_handled_description);
			break;
		}

		case lb::codes::to_wide_string_failed:
		{
			output_window(to_wide_string_failed_description);
			break;
		}

		case lb::codes::to_narrow_string_failed:
		{
			output_window(to_narrow_string_failed_description);
			break;
		}

		case lb::codes::memory_leak:
		{
			output_window(memory_leak_description);
			break;
		}

		case lb::codes::filesystem_error:
		{
			output_window(filesystem_error_description);
			break;
		}

		case lb::codes::test_failed:
		{
			output_window(test_failed_description);
			break;
		}

		case lb::codes::test_success:
		{
			output_window(test_success_description);
			break;
		}
			

		case lb::codes::menu_error:
		{
			output_window(menu_error_description);
			break;
		}

		case lb::codes::HWND_error:
		{
			output_window(HWND_error_description);
			break;
		}

		case lb::codes::register_class_fail:
		{
			output_window(register_class_fail_description);
			break;
		}

		case lb::codes::get_client_rect_fail:
		{
			output_window(get_client_rect_fail_description);
			break;
		}

		case lb::codes::invalidate_rect_fail:
		{
			output_window(invalidate_rect_fail_description);
			break;
		}

		case lb::codes::font_error:
		{
			output_window(font_error_description);
			break;
		}

		case lb::codes::null:
		{
			output_window(null_description);
			break;
		}

		default:
			output_window(ROS("Unknown error code."));
			break;
	}
}


lol_blocks::string lol_blocks::get_location(std::source_location sl)
{
	std::string function_name = sl.function_name();
	std::string line = std::to_string(sl.line());
	std::string column = std::to_string(sl.column());
	std::string file_name = sl.file_name();

	std::string temp = std::format("File name: {} \n - column: {} \n - line: {} \n - function name: {} \n", file_name, column, line, function_name);
#if USING_NARROW_STRINGS
	return temp;
#endif

#if USING_WIDE_STRINGS
	std::wstring temp_wide;
	{
		lb::codes code;
		temp_wide = to_wide_string(temp, &code);
		output_code(code);
	}
	return temp_wide;
#endif
}

lol_blocks::string lol_blocks::get_last_error_win32()
{
	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0) {
		return {}; // No error message has been recorded 
	}

	w32_str_p messageBuffer = nullptr;

	// Format the error message 
	size_t size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorMessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(w32_str_p)&messageBuffer,
		0,
		NULL
	);

	// Copy the error message into a wide string
	string message(messageBuffer, size);

	// Free the buffer allocated by FormatMessage 
	LocalFree(messageBuffer);

	return message;
}


std::wstring lol_blocks::to_wide_string(const std::string& narrow, lb::codes* code)
{
	/*

	std::size_t mbsrtowcs( wchar_t* dst,
					   const char** src,
					   std::size_t len,
					   std::mbstate_t* ps );

	dst 	- 	pointer to wide character array where the results will be stored
	src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
	len 	- 	number of wide characters available in the array pointed to by dst
	ps 	- 	pointer to the conversion state object

	*/

	// Create a fresh conversion state per thread
	std::mbstate_t state = std::mbstate_t();

	// temp in order to get the address of the pointer
	const char* temp = narrow.c_str();

	// get the length in bytes of "temp"
	std::size_t length = 1 + std::mbsrtowcs(nullptr, &temp, 0, &state);

	// stack buffer
	wchar_t* buffer = nullptr;
	wchar_t stack_buffer[max_string_buffer];
	bool heap_allocated = false;

	// if length is greater than max_string_buffer, we will allocate a new buffer using new
	if (length > max_string_buffer) {
		buffer = new wchar_t[length];
		heap_allocated = true;
	}
	else {
		buffer = stack_buffer;
	}

	// according to documentation:
	/*

	The following functions should not be called from multiple threads without synchronization with
	the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
	std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

	*/
	std::size_t error_code = std::mbsrtowcs(buffer, &temp, length, &state);

	// On conversion error (if invalid wide character was encountered), 
	// returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
	if (error_code == std::size_t(-1)) {

		*code = lb::codes::to_wide_string_failed;

		// clean up
		if (heap_allocated == true and buffer != nullptr) {
			delete[] buffer;
		}

		// returns an empty string
		return {};
	}

	// clean up
	if (heap_allocated == true and buffer != nullptr) {
		std::wstring r_temp(buffer);
		delete[] buffer;
		return r_temp;
	}

	*code = lb::codes::success;

	// return the wide string using the buffer
	return std::wstring(buffer);
}


std::string lol_blocks::to_narrow_string(const std::wstring& wide, lb::codes* code)
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

   // Create a fresh conversion state per thread
	std::mbstate_t state = std::mbstate_t();

	// get the wide string length, does not include '\0'
	// returns the length in bytes
	const wchar_t* temp = wide.c_str();
	std::size_t length = 1 + std::wcsrtombs(nullptr, &temp, 0, &state);

	// stack buffer
	char* buffer = nullptr;
	char stack_buffer[max_string_buffer];
	bool heap_allocated = false;

	// if length is greater than max_string_buffer, we will allocate a new buffer using new
	if (length > max_string_buffer) {
		buffer = new char[length];
		heap_allocated = true;
	}
	else {
		buffer = stack_buffer;
	}

	// according to documentation:
	/*

	The following functions should not be called from multiple threads without synchronization with
	the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
	std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

	*/

	std::size_t error_code = std::wcsrtombs(buffer, &temp, length, &state);


	// On conversion error (if invalid wide character was encountered), 
	// returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
	if (error_code == std::size_t(-1)) {

		*code = lb::codes::to_narrow_string_failed;
		
		// clean up
		if (heap_allocated == true and buffer != nullptr) {
			delete[] buffer;
		}

		// returns an empty string
		return {};
	}

	// clean up
	if (heap_allocated == true and buffer != nullptr) {
		std::string r_temp(buffer);
		delete[] buffer;
		return r_temp;
	}

	*code = lb::codes::success;

	// return the narrow string using the stack buffer
	return std::string(buffer);
}

void lol_blocks::output_window(const string& message, const string& title)
{
	MessageBox(
		nullptr,                // No owner window
		message.c_str(),        // Error message
		title.c_str(),          // Title of the message box
		MB_OK | MB_ICONERROR    // OK button with an error icon
	);
}