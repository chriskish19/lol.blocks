#include "base/header/logging.hpp"

win32gui::logging::logging(std::initializer_list<win32gui::win32gui_error_codes> codes) noexcept
	:errors(codes)
{

}

win32gui::logging::logging(std::wstring const& error_message) noexcept
{

}

std::wstring win32gui::logging::get_last_Error_win32() noexcept
{
	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0) {
		return {}; // No error message has been recorded 
	}

	LPWSTR messageBuffer = nullptr;

	// Format the error message 
	size_t size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, 
		errorMessageID, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		(LPWSTR)&messageBuffer, 
		0, 
		NULL
	);

	// Copy the error message into a wide string
	std::wstring message(messageBuffer, size);

	// Free the buffer allocated by FormatMessage 
	LocalFree(messageBuffer);

	return message;
}

win32gui::win32gui_error_codes win32gui::logging::send_to_log_window() noexcept
{
	return win32gui::win32gui_error_codes();
}
