/****************************************************************
	Header: globals.hpp

	Purpose: global objects/variables/functions needed for
			 lol.blocks.

****************************************************************/

// NOTE: See class headers for where globals can and cannot be used.

#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// error coes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/system_log_window.hpp"

namespace global {
	extern std::atomic<window::log_window*>* log_window_p;
	extern std::atomic<bool>* all_display_windows_closed;


	void log_to_system_log_window(const string& message);
	void clean_up();
}