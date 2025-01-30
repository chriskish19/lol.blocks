/****************************************************************
	Header: system_log_window.hpp

	Purpose: creates a log window with its own message pump.

****************************************************************/




#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"

namespace window {
	class system_log_window : public log_window {
	public:
		system_log_window() = default;

		// setup the window and run message pump
		errors::codes go() override;

	private:
		void window_settings() override;
		void create_window() override;
		WNDCLASS m_slw_wc = {};
		string m_slw_class_name = READ_ONLY_STRING("system log window");
		string m_slw_title = READ_ONLY_STRING("SYSTEM LOG WINDOW");
	};
}