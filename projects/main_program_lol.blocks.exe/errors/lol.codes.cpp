#include "lol.codes.hpp"

errors::win32_error::win32_error(const string& location) noexcept
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

errors::string errors::win32_error::full_error_message() noexcept
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

void errors::handle_error_codes(errors::codes code, const string& location) noexcept
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
			win32_error w32er(location);
			show_error_message_window(w32er.full_error_message(), w32er.get_code_string());
			break;
		}

		case codes::pointer_is_nullptr:
		{
			pointer_is_nullptr p_null(READ_ONLY_STRING("name of pointer variable not set"),location);
			show_error_message_window(p_null.full_error_message(), p_null.get_code_string());
			break;
		}

		case codes::get_client_rect_failed:
		{
			get_client_rect_failed rect_err;
			show_error_message_window(rect_err.full_error_message(), rect_err.get_code_string());
			break;
		}

		case codes::win32_HWND_error:
		{
			win32_HWND_error w32er;
			show_error_message_window(w32er.full_error_message(), w32er.get_code_string());
			break;
		}

		case codes::win32_register_class_fail:
		{
			win32_register_class_fail w32er(location);
			show_error_message_window(w32er.full_error_message(), w32er.get_code_string());
			break;
		}

		// finish adding the rest!!

		default:
			show_error_message_window(get_location(), READ_ONLY_STRING("code not found:"));
	}
}

errors::dx_error::dx_error(HRESULT hr, const string& location) noexcept
	:m_location(location)
{
	translate_HRESULT(hr);

}

errors::dx_error::dx_error(HRESULT hr, ID3DBlob* error, const string& location) noexcept
	:m_location(location)
{
	translate_HRESULT(hr);
	translate_error_blob(error);
}

errors::dx_error::dx_error(HRESULT hr, ID3D11InfoQueue* debug_info_p, const string& location) noexcept
	:m_location(location)
{
	
#if ENABLE_FULL_DEBUG
	
	if (debug_info_p == nullptr) {

		errors::handle_error_codes(errors::codes::pointer_is_nullptr);

	}
	
#endif


	translate_HRESULT(hr);
	translate_debug_info(debug_info_p);
}

errors::string errors::dx_error::full_error_message() noexcept
{
	return m_info + 
		READ_ONLY_STRING("\n") + 
		m_location + 
		READ_ONLY_STRING("\n") + 
		m_dx_error_blob_str + 
		READ_ONLY_STRING("\n") + 
		m_debug_info_str;
}

void errors::dx_error::translate_HRESULT(HRESULT hr) noexcept
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
		handle_error_codes(codes::pointer_is_nullptr);
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

errors::string errors::pointer_is_nullptr::full_error_message() noexcept
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n") + m_pointer_name;
}

errors::string errors::get_client_rect_failed::full_error_message() noexcept
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n");
}

errors::string errors::win32_HWND_error::full_error_message() noexcept
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n");
}

errors::string errors::win32_register_class_fail::full_error_message() noexcept
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n");
}

errors::string errors::base_error::full_error_message() noexcept
{
	return string(READ_ONLY_STRING("base error class"));
}

errors::string errors::base_error::get_code_string() noexcept
{
	return string(READ_ONLY_STRING("base error code"));
}

errors::string errors::win32_menu_error::full_error_message() noexcept
{
	return m_info + READ_ONLY_STRING("\n") + m_location + READ_ONLY_STRING("\n");
}
