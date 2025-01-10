// class header include
#include "logging_sys.hpp"

std::wstring utilities::log_info::get_last_error_win32() noexcept
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

std::wstring utilities::log_info::get_last_error_lol_blocks() noexcept
{
	return L"";
}
