/****************************************************************
* File: lol_codes.hpp
*
* Purpose: error codes and definitions
*
* Used: anywhere in lol blocks
****************************************************************/

// NOTES: This header is designed to be used anywhere and everywhere in lol.blocks
// it doesnt depend on any classes...


#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH

namespace lol_blocks {
	inline const character* menu_error_description =				ROS("win32_codes: menu_error, an issue with when creating a menu item using CreateMenu()");
	inline const character* HWND_error_description =				ROS("win32_codes: HWND_error, the window handle is nullptr");
	inline const character* register_class_fail_description =		ROS("win32_codes: register_class_fail, issue when calling RegisterClass()");
	inline const character* get_client_rect_fail_description =		ROS("win32_codes: get_client_rect_fail, issue when trying to obtain the client window size using GetClientRect()");
	inline const character* invalidate_rect_fail_description =		ROS("win32_codes: invalidate_rect_fail, issue when calling the function InvalidateRect()");
	inline const character* font_error_description =				ROS("win32_codes: font_error, a problem when creating a new font. The function CreateFont() failed");
	inline const character* null_description =						ROS("win32_codes: null, n/a");

	inline const character* success_description =											ROS("codes: success, successful execution");
	inline const character* pointer_is_nullptr_description =								ROS("codes: pointer_is_nullptr, pointer has no memory to point to");
	inline const character* wide_string_copy_fail_wcs_cpy_description =						ROS("codes: wide_string_copy_fail_wcs_cpy, wide string copy function failed to copy the string");
	inline const character* strings_not_equal_description =									ROS("codes: strings_not_equal, the two strings you are comparing are different in size or characters");
	inline const character* empty_string_description =										ROS("codes: empty_string, the string is empty. no characters.");
	inline const character* string_length_too_long_description =							ROS("codes: string_length_too_long, the strings length is too long for this function to procced");
	inline const character* index_out_of_range_description =								ROS("codes: index_out_of_range, you are trying to access an array/vector using an index that is non existant in the array/vector");
	inline const character* division_by_zero_description =									ROS("codes: division_by_zero, trying to divide by zero is undefined");
	inline const character* unknown_keyboard_key_in_system_message_handler_description =	ROS("codes: unknown_keyboard_key_in_system_message_handler, where key presses are handled in the program a key has been pressed that is not known");
	inline const character* unknown_mouse_button_in_system_message_handler_description =	ROS("codes: unknown_mouse_button_in_system_message_handler, where mouse button presses are handled in the program a mouse button has been pressed which is not known");
	inline const character* dx_error_description =											ROS("codes: dx_error, a direct x error has occurred");
	inline const character* exception_thrown_and_handled_description =						ROS("codes: exception_thrown_and_handled, an exception has occurred and has been caught and handled");
	inline const character* to_wide_string_failed_description =								ROS("codes: to_wide_string_failed, converting a narrow string to wide string has failed");
	inline const character* to_narrow_string_failed_description =							ROS("codes: to_narrow_string_failed, converting a wide string to narrow has failed");
	inline const character* memory_leak_description =										ROS("codes: memory_leak, allocated memory but didnt call delete on it!");
	inline const character* filesystem_error_description =									ROS("codes: filesystem_error, an error doing file operations has occurred. Check file system error codes.");
	inline const character* test_success_description =										ROS("codes: test_success, no errors test completed successfully...");
	inline const character* test_failed_description =										ROS("codes: test_failed, error occurred during testing");
	inline const character* uninitialized_description =										ROS("codes: error code is not set");
	
	enum class codes {
		success = 0,
		uninitialized,
		pointer_is_nullptr,
		wide_string_copy_fail_wcs_cpy,
		strings_not_equal,
		empty_string,
		string_length_too_long,
		index_out_of_range,
		division_by_zero,
		unknown_keyboard_key_in_system_message_handler,
		unknown_mouse_button_in_system_message_handler,
		dx_error,
		exception_thrown_and_handled,
		to_wide_string_failed,
		to_narrow_string_failed,
		memory_leak,
		filesystem_error,
		test_failed,
		test_success,
		menu_error,
		HWND_error,
		register_class_fail,
		get_client_rect_fail,
		invalidate_rect_fail,
		font_error,
		null
	};
}









