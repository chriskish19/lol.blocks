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
	
	// dx errors
	inline const character* dx_access_denied_description = ROS("You tried to use a resource to which you did not have the required access privileges. This error is most typically caused when you write to a shared resource with read-only access.");
	inline const character* dx_access_lost_description = ROS("The desktop duplication interface is invalid. The desktop duplication interface typically becomes invalid when a different type of image is displayed on the desktop.");
	inline const character* dx_already_exists_description = ROS("The desired element already exists. This is returned by DXGIDeclareAdapterRemovalSupport if it is not the first time that the function is called.");
	inline const character* dx_cannot_protect_content_description = ROS("DXGI can't provide content protection on the swap chain. This error is typically caused by an older driver, or when you use a swap chain that is incompatible with content protection.");
	inline const character* dx_device_hung_description = ROS("The application's device failed due to badly formed commands sent by the application. This is an design-time issue that should be investigated and fixed.");
	inline const character* dx_device_removed_description = ROS("The video card has been physically removed from the system, or a driver upgrade for the video card has occurred. The application should destroy and recreate the device. For help debugging the problem, call ID3D10Device::GetDeviceRemovedReason.");
	inline const character* dx_device_reset_description = ROS("The device failed due to a badly formed command. This is a run-time issue; The application should destroy and recreate the device.");
	inline const character* dx_driver_internal_error_description = ROS("The driver encountered a problem and was put into the device removed state.");
	inline const character* dx_frame_statistics_disjoint_description = ROS("An event (for example, a power cycle) interrupted the gathering of presentation statistics.");
	inline const character* dx_graphics_vidpn_source_in_use_description = ROS("The application attempted to acquire exclusive ownership of an output, but failed because some other application (or device within the application) already acquired ownership.");
	inline const character* dx_invalid_call_description = ROS("The application provided invalid parameter data; this must be debugged and fixed before the application is released.");
	inline const character* dx_more_data_description = ROS("The buffer supplied by the application is not big enough to hold the requested data.");
	inline const character* dx_name_already_exists_description = ROS("The supplied name of a resource in a call to IDXGIResource1::CreateSharedHandle is already associated with some other resource.");
	inline const character* dx_nonexclusive_description = ROS("A global counter resource is in use, and the Direct3D device can't currently use the counter resource.");
	inline const character* dx_not_currently_avaliable_description = ROS("The resource or request is not currently available, but it might become available later.");
	inline const character* dx_not_found_description = ROS("When calling IDXGIObject::GetPrivateData, the GUID passed in is not recognized as one previously passed to IDXGIObject::SetPrivateData or IDXGIObject::SetPrivateDataInterface. When calling IDXGIFactory::EnumAdapters or IDXGIAdapter::EnumOutputs, the enumerated ordinal is out of range.");
	inline const character* dx_remote_client_disconnected_description = ROS("The applications remote device has been removed.");
	inline const character* dx_remote_outofmemory_description = ROS("The session has ended because the remote computer ran out of memory.");
	inline const character* dx_restrict_to_output_stale_description = ROS("The DXGI output (monitor) to which the swap chain content was restricted is now disconnected or changed.");
	inline const character* dx_sdk_component_missing_description = ROS("The operation depends on an SDK component that is missing or mismatched.");
	inline const character* dx_session_disconnected_description = ROS("The Remote Desktop Services session is currently disconnected.");
	inline const character* dx_unsupported_description = ROS("The requested functionality is not supported by the device or the driver.");
	inline const character* dx_wait_timeout_description = ROS("The time-out interval elapsed before the next desktop frame was available.");
	inline const character* dx_was_still_drawing_description = ROS("The GPU was busy at the moment when a call was made to perform an operation, and did not execute or schedule the operation.");
	inline const character* dx_ok_description = ROS("The method succeeded without an error.");
	inline const character* dx_unknown_code_description = ROS("unknown dx code");








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
		null,

		// dx errors
		dx_access_denied,
		dx_access_lost,
		dx_already_exists,
		dx_cannot_protect_content,
		dx_device_hung,
		dx_device_removed,
		dx_device_reset,
		dx_driver_internal_error,
		dx_frame_statistics_disjoint,
		dx_graphics_vidpn_source_in_use,
		dx_invalid_call,
		dx_more_data,
		dx_name_already_exists,
		dx_nonexclusive,
		dx_not_currently_avaliable,
		dx_not_found,
		dx_remote_client_disconnected,
		dx_remote_outofmemory,
		dx_restrict_to_output_stale,
		dx_sdk_component_missing,
		dx_session_disconnected,
		dx_unsupported,
		dx_wait_timeout,
		dx_was_still_drawing,
		dx_ok,
		dx_unknown_code
	};
}







