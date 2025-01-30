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

namespace utilities {
	// checks the menu pointer from CreateMenu()
	errors::codes win32_menu_check(HMENU p_menu,const string& location = errors::get_location());

	// checks the function AppendMenu() return value and handles the error
	errors::codes win32_append_menu_check(BOOL code, const string& location = errors::get_location());
}