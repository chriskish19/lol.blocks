/****************************************************************
	Header: lol.api.hpp

	Purpose: helper functions 

****************************************************************/


#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// errors
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"


namespace utilities {
	// string conversions
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);

	// string conversions with error codes
	std::wstring to_wide_string(const char* narrow,errors::codes* code_p=nullptr);
	std::wstring to_wide_string(const std::string& narrow, errors::codes* code_p = nullptr);
	std::string to_narrow_string(const wchar_t* wide, errors::codes* code_p = nullptr);
	std::string to_narrow_string(const std::wstring& wide, errors::codes* code_p = nullptr);


	// checks the menu pointer from CreateMenu()
	errors::win32_codes win32_menu_check(HMENU p_menu,const string& location = errors::get_location());

	// checks the function AppendMenu() return value and handles the error
	errors::win32_codes win32_append_menu_check(BOOL code, const string& location = errors::get_location());

	errors::codes is_path_valid(const std::filesystem::path& path);

	errors::codes create_directories(const std::filesystem::path& path);
}