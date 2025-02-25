#include "lol.codes.hpp"


namespace code_error_objs {
	using namespace errors;

	any_two<codes, string>* success = new any_two<codes, string>(codes::success, errors_cstr::success);
	any_two<codes, string>* pointer_is_nullptr = new any_two<codes, string>(codes::pointer_is_nullptr, errors_cstr::pointer_is_nullptr);
	any_two<codes, string>* wide_string_copy_fail_wcs_cpy = new any_two<codes, string>(codes::wide_string_copy_fail_wcs_cpy, errors_cstr::wide_string_copy_fail_wcs_cpy);
	any_two<codes, string>* strings_not_equal = new any_two<codes, string>(codes::strings_not_equal, errors_cstr::strings_not_equal);
	any_two<codes, string>* empty_string = new any_two<codes, string>(codes::empty_string, errors_cstr::empty_string);
	any_two<codes, string>* division_by_zero = new any_two<codes, string>(codes::division_by_zero, errors_cstr::division_by_zero);
	any_two<codes, string>* unknown_keyboard_key_in_system_message_handler = new any_two<codes, string>(codes::unknown_keyboard_key_in_system_message_handler, errors_cstr::unknown_keyboard_key_in_system_message_handler);
	any_two<codes, string>* unknown_mouse_button_in_system_message_handler = new any_two<codes, string>(codes::unknown_mouse_button_in_system_message_handler, errors_cstr::unknown_mouse_button_in_system_message_handler);
	any_two<codes, string>* dx_error = new any_two<codes, string>(codes::dx_error, errors_cstr::dx_error);
	any_two<codes, string>* exception_thrown_and_handled = new any_two<codes, string>(codes::exception_thrown_and_handled, errors_cstr::exception_thrown_and_handled);
	any_two<codes, string>* to_wide_string_failed = new any_two<codes, string>(codes::to_wide_string_failed, errors_cstr::to_wide_string_failed);
	any_two<codes, string>* to_narrow_string_failed = new any_two<codes, string>(codes::to_narrow_string_failed, errors_cstr::to_narrow_string_failed);
	any_two<codes, string>* string_length_too_long = new any_two<codes, string>(codes::string_length_too_long, errors_cstr::string_length_too_long);
	any_two<codes, string>* index_out_of_range = new any_two<codes, string>(codes::index_out_of_range, errors_cstr::index_out_of_range);
	any_two<codes, string>* memory_leak = new any_two<codes, string>(codes::memory_leak, errors_cstr::memory_leak);
	any_two<codes, string>* filesystem_error = new any_two<codes, string>(codes::filesystem_error, errors_cstr::filesystem_error);

	void clean_up() {
		if (success != nullptr) {
			delete success;
			success = nullptr;
		}

		if (pointer_is_nullptr != nullptr) {
			delete pointer_is_nullptr;
			pointer_is_nullptr = nullptr;
		}

		if (wide_string_copy_fail_wcs_cpy != nullptr) {
			delete wide_string_copy_fail_wcs_cpy;
			wide_string_copy_fail_wcs_cpy = nullptr;
		}

		if (strings_not_equal != nullptr) {
			delete strings_not_equal;
			strings_not_equal = nullptr;
		}

		if (empty_string != nullptr) {
			delete empty_string;
			empty_string = nullptr;
		}

		if (string_length_too_long != nullptr) {
			delete string_length_too_long;
			string_length_too_long = nullptr;
		}

		if (index_out_of_range != nullptr) {
			delete index_out_of_range;
			index_out_of_range = nullptr;
		}

		if (division_by_zero != nullptr) {
			delete division_by_zero;
			division_by_zero = nullptr;
		}

		if (unknown_keyboard_key_in_system_message_handler != nullptr) {
			delete unknown_keyboard_key_in_system_message_handler;
			unknown_keyboard_key_in_system_message_handler = nullptr;
		}

		if (unknown_mouse_button_in_system_message_handler != nullptr) {
			delete unknown_mouse_button_in_system_message_handler;
			unknown_mouse_button_in_system_message_handler = nullptr;
		}

		if (dx_error != nullptr) {
			delete dx_error;
			dx_error = nullptr;
		}

		if (exception_thrown_and_handled != nullptr) {
			delete exception_thrown_and_handled;
			exception_thrown_and_handled = nullptr;
		}

		if (to_wide_string_failed != nullptr) {
			delete to_wide_string_failed;
			to_wide_string_failed = nullptr;
		}

		if (to_narrow_string_failed != nullptr) {
			delete to_narrow_string_failed;
			to_narrow_string_failed = nullptr;
		}

		if (memory_leak != nullptr) {
			delete memory_leak;
			memory_leak = nullptr;
		}

		if (filesystem_error != nullptr) {
			delete filesystem_error;
			filesystem_error = nullptr;
		}
	}
}


namespace win32_code_objs {
	using namespace errors;

	any_two<win32_codes, string>* success = new any_two<win32_codes, string>(win32_codes::success, w32errors_cstr::success);
	any_two<win32_codes, string>* menu_error = new any_two<win32_codes, string>(win32_codes::menu_error, w32errors_cstr::menu_error);
	any_two<win32_codes, string>* HWND_error = new any_two<win32_codes, string>(win32_codes::HWND_error, w32errors_cstr::HWND_error);
	any_two<win32_codes, string>* register_class_fail = new any_two<win32_codes, string>(win32_codes::register_class_fail, w32errors_cstr::register_class_fail);
	any_two<win32_codes, string>* get_client_rect_fail = new any_two<win32_codes, string>(win32_codes::get_client_rect_fail, w32errors_cstr::get_client_rect_fail);
	any_two<win32_codes, string>* invalidate_rect_fail = new any_two<win32_codes, string>(win32_codes::invalidate_rect_fail, w32errors_cstr::invalidate_rect_fail);
	any_two<win32_codes, string>* font_error = new any_two<win32_codes, string>(win32_codes::font_error, w32errors_cstr::font_error);
	any_two<win32_codes, string>* null = new any_two<win32_codes, string>(win32_codes::null, w32errors_cstr::null);

	void clean_up() {
		if (success != nullptr) {
			delete success;
			success = nullptr;
		}

		if (menu_error != nullptr) {
			delete menu_error;
			menu_error = nullptr;
		}

		if (HWND_error != nullptr) {
			delete HWND_error;
			HWND_error = nullptr;
		}

		if (register_class_fail != nullptr) {
			delete register_class_fail;
			register_class_fail = nullptr;
		}

		if (get_client_rect_fail != nullptr) {
			delete get_client_rect_fail;
			get_client_rect_fail = nullptr;
		}

		if (invalidate_rect_fail != nullptr) {
			delete invalidate_rect_fail;
			invalidate_rect_fail = nullptr;
		}

		if (font_error != nullptr) {
			delete font_error;
			font_error = nullptr;
		}

		if (null != nullptr) {
			delete null;
			null = nullptr;
		}
	}
}

errors::string errors::get_location(std::source_location sl)
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
	return to_wide_string(temp);
#endif
}

errors::string errors::get_last_error_win32()
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

// this function is very slow but its only used for exception classes so it doesnt matter
std::wstring errors::to_wide_string(const std::string& narrow)
{	
	size_t length = narrow.length();
	wchar_t* buffer = new wchar_t[length];

	if (std::mbstowcs(buffer, narrow.c_str(), length) == (size_t)-1) {
		if (buffer != nullptr) {
			delete[] buffer;
		}
		return {};
	}
	std::wstring temp(buffer);
	if (buffer != nullptr) {
		delete[] buffer;
	}
	return temp;
}

// this function is very slow but its only used for exception classes so it doesnt matter
std::string errors::to_narrow_string(const std::wstring& wide)
{
	size_t length = wide.length();
	char* buffer = new char[length];
	
	if (std::wcstombs(buffer, wide.c_str(), length) == (size_t)-1) {
		if (buffer != nullptr) {
			delete[] buffer;
		}
		return {};
	}
	std::string temp(buffer);
	if (buffer != nullptr) {
		delete[] buffer;
	}
	return temp;
}

void errors::show_error_message_window(const string& message, const string& title)
{
	MessageBox(
		nullptr,                // No owner window
		message.c_str(),        // Error message
		title.c_str(),          // Title of the message box
		MB_OK | MB_ICONERROR    // OK button with an error icon
	);
}

errors::dx_error::dx_error(code_error_objs::code_obj& code ,HRESULT hr, const string& location) noexcept
	:basic_error<codes>(code.output()),m_location(location)
{
	translate_HRESULT(hr);

}

errors::dx_error::dx_error(code_error_objs::code_obj& code, HRESULT hr, ID3DBlob* error, const string& location) noexcept
	:basic_error<codes>(code.output()),m_location(location)
{
	translate_HRESULT(hr);
	translate_error_blob(error);
}

errors::dx_error::dx_error(code_error_objs::code_obj& code, HRESULT hr, ID3D11InfoQueue* debug_info_p, const string& location) noexcept
	:basic_error<codes>(code.output()),m_location(location)
{
	
#if ENABLE_FULL_DEBUG
	if (debug_info_p == nullptr) {
		errors::handle_basic_error_codes(errors::codes::pointer_is_nullptr);
	}
#endif


	translate_HRESULT(hr);
	translate_debug_info(debug_info_p);
}

void errors::dx_error::translate_HRESULT(HRESULT hr) noexcept
{
	_com_error err(hr);
	LPCWSTR errMsg = err.ErrorMessage();

	// make a wide temp copy
	std::wstring err_temp(errMsg);

	// convert if necessary
#if USING_NARROW_STRINGS
	m_hr_str += to_narrow_string(err_temp);
#endif

#if USING_WIDE_STRINGS
	m_hr_str += err_temp;
#endif
}

void errors::dx_error::translate_error_blob(ID3DBlob* error) noexcept
{
	if (error == nullptr) {
		return;
	}
	// Get the error message from the blob
	const char* errorMessage = static_cast<const char*>(error->GetBufferPointer());
	size_t messageSize = error->GetBufferSize();

	// Convert it to a std::string
	std::string temp_error_str(errorMessage, messageSize);

	// convert if necessary
#if USING_NARROW_STRINGS
	m_dx_error_blob_str = temp_error_str;
#endif

#if USING_WIDE_STRINGS
	m_dx_error_blob_str = to_wide_string(temp_error_str);
#endif
}

void errors::dx_error::translate_debug_info(ID3D11InfoQueue* debug_info_p) noexcept
{
	/*
	
	typedef struct D3D11_MESSAGE {
	  D3D11_MESSAGE_CATEGORY Category;
	  D3D11_MESSAGE_SEVERITY Severity;
	  D3D11_MESSAGE_ID       ID;
	  const char             *pDescription;
	  SIZE_T                 DescriptionByteLength;
	} D3D11_MESSAGE;
	
	*/
	
	
	// Get the size of the message
	SIZE_T messageLength = 0;
	HRESULT hr = debug_info_p->GetMessage(0, NULL, &messageLength);

	// Allocate space and get the message
	D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*)malloc(messageLength);
	hr = debug_info_p->GetMessage(0, pMessage, &messageLength);

	if (pMessage == nullptr) {
		handle_basic_error_codes(codes::pointer_is_nullptr);
		return;
	}

	std::string temp(pMessage->pDescription, pMessage->DescriptionByteLength);
	
#if USING_NARROW_STRINGS

	m_debug_info_str = temp;

#endif

#if USING_WIDE_STRINGS

	m_debug_info_str = to_wide_string(temp);

#endif

	if (pMessage != nullptr) {
		free( pMessage );
	}
}

void errors::handle_basic_error_codes(codes code, const string& location) noexcept
{
	switch (code) {
		case codes::success: 
		{
			return;
		}
		
		case codes::division_by_zero:
		{

		}

		default:
			show_error_message_window(READ_ONLY_STRING("error code not found!"));
	}
}

void errors::handle_win32_error_codes(win32_codes code, const string& location) noexcept
{
	switch (code) {
		case win32_codes::success:
		{
			return;
		}

		default:
			show_error_message_window(READ_ONLY_STRING("error code not found!"));
	}
}
