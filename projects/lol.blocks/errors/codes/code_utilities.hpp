/***********************************************
* File: code_utilities.hpp
*
* Purpose: utilities used within error handling
*
* Used: within the folder errors
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH



namespace lol_blocks {
	// sends error information to a pop window
	void output_code(lb::codes code);
	
	// returns the location of the function call site, used in exceptions classes constructor
	string get_location(std::source_location sl = std::source_location::current());

	// if there is no error an empty string is returned
	string get_last_error_win32();

	// if these functions fail they return an empty string.
	// if max_string_buffer is exceeded then new is used to allocate memory
	const std::size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const std::string& narrow,lb::codes* code);
	std::string to_narrow_string(const std::wstring& wide, lb::codes* code);

	// a message box window that will display errors, for when system log window cant be used
	// or for pessky debug errors
	void output_window(const string& message, const string& title = ROS("ERROR WINDOW"));
}