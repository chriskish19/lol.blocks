/****************************************************************
	Header: pch.hpp

	Purpose: includes all the headers needed for entry point.
			 

****************************************************************/


#ifndef PRE_COMPILED_HEADER_HPP
#define PRE_COMPILED_HEADER_HPP

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// direct x api
#include "main_program_lol.blocks.exe/dependencies/dx_api/directx_includes.hpp"

// error codes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"

// utilities classes
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/logging_sys.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"

// window classes
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class_mt.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"


#endif