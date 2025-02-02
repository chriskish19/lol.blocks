/****************************************************************
	Header: globals.hpp

	Purpose: global objects/variables/functions needed for
			 lol.blocks.

****************************************************************/

// NOTE: See class headers for where globals can and cannot be used.

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// error codes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/classes/window/logging/log_window_class.hpp"
#include "main_program_lol.blocks.exe/classes/window/logging/system_log_window.hpp"

namespace global {
	// system log window
	extern std::atomic<window::log_window*>* log_window_p;

	// for future use
	extern std::atomic<bool>* all_display_windows_closed;

	// send a message to the system log window
	void log_to_system_log_window(const string& message);

	// deletes global objects
	void clean_up();
}