#include "lol.codes.hpp"

errors::win32_error::win32_error(std::source_location sl)
	:m_sl(sl)
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

errors::string errors::win32_error::get_location()
{
	return std::format(READ_ONLY_STRING("File name: {} - column: {} - line: {} - function name: {}"), 
		m_sl.file_name(), m_sl.column(), m_sl.line(), m_sl.function_name());
}

errors::codes errors::win32_error::send_to_window(HWND window_handle) noexcept
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_handle, &ps);

	// Set text color and background
	SetTextColor(hdc, RGB(0, 0, 0));       // Black text
	SetBkColor(hdc, RGB(255, 255, 255));  // White background

	// Display the current string
	RECT rect;
	GetClientRect(window_handle, &rect);
	DrawText(hdc, m_info.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	EndPaint(window_handle, &ps);

	return codes::success;
}

errors::string errors::pointer_is_nullptr::get_location()
{
	return std::format(READ_ONLY_STRING("File name: {} - column: {} - line: {} - function name: {}"),
		m_sl.file_name(), m_sl.column(), m_sl.line(), m_sl.function_name());
}
