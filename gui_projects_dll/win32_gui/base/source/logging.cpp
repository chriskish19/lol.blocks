// dependencies
#include "../../dependencies/macros/win32gui_macro_import.hpp"
#include "../../dependencies/stl/win32gui_stl.hpp"
#include "../../dependencies/windows_api/win32_header_includes.hpp"

// class include dependants
#include "../header/errors.hpp"  // log_window and window_base use error_codes
#include "../header/ground.hpp"  // log_window inherits window_base
#include "../header/log_window.hpp"

// class definition header
#include "../header/logging.hpp"

win32gui::logging::logging(HWND parent_window) noexcept
	:log_window(L"Logging Window",parent_window)
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
	std::wstring current_error_message = this->get_last_Error_win32();
	if (current_error_message.empty()) {
		this->add_display_message_in_window(L"No win32 errors present");
	}
	
	
	return win32gui::win32gui_error_codes();
}
