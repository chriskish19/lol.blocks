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

	enum class codes {
		// custom error codes
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
		null,
		unknown
	};
}