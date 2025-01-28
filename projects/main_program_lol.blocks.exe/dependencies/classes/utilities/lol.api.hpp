/****************************************************************
	Header: lol.api.hpp

	Purpose: helper functions 

****************************************************************/


#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// d3d api
#include "main_program_lol.blocks.exe/dependencies/dx_api/directx_includes.hpp"

// errors
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

namespace utilities {
	// checks the menu pointer from CreateMenu()
	errors::codes win32_menu_check(HMENU p_menu,const string& location = errors::get_location());

	// checks the function AppendMenu() return value and handles the error
	errors::codes win32_append_menu_check(BOOL code, const string& location = errors::get_location());
}