#include "lol.codes.hpp"

errors::win32_error::win32_error(const string& location)
	:m_location(location)
{
}

errors::string errors::win32_error::get_last_error_win32() noexcept
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

errors::string errors::win32_error::full_error_message()
{
	return m_info + m_location;
}

errors::string errors::get_location(std::source_location sl)
{
	std::string function_name = sl.function_name();
	std::string line = std::to_string(sl.line());
	std::string column = std::to_string(sl.column());
	std::string file_name = sl.file_name();

	std::string temp = std::format("File name: {} - column: {} - line: {} - function name: {}", file_name, column, line, function_name);
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

void errors::handle_error_codes(errors::codes code)
{
	switch (code) 
	{
		// deal with this right away since its not an error
		case codes::success:
		{
			return;
		}
	
		case codes::win32_error:
		{
			win32_error w32er;
			show_error_message_window(w32er.full_error_message(), w32er.get_code_string());
			break;
		}

		case codes::pointer_is_nullptr:
		{
			pointer_is_nullptr p_null(READ_ONLY_STRING("name of pointer variable not set"));
			show_error_message_window(p_null.full_error_message(), p_null.get_error_code_string());
			break;
		}

		// finish adding the rest!!

		default:
			show_error_message_window(get_location(), READ_ONLY_STRING("code not found:"));
	}
}

errors::dx_error::dx_error(HRESULT hr)
{
	_com_error err(hr);
	LPCWSTR errMsg = err.ErrorMessage();
	
	// make a wide temp copy
	std::wstring err_temp(errMsg);

	// convert if necessary
#if USING_NARROW_STRINGS
	m_info += to_narrow_string(err_temp);
#endif

#if USING_WIDE_STRINGS
	m_info += err_temp;
#endif
}

errors::string errors::pointer_is_nullptr::full_error_message()
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n") + m_pointer_name;
}
