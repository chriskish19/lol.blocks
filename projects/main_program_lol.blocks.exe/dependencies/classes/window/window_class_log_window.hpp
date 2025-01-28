/****************************************************************
	Header: window_class_log_window.hpp

	Purpose: creates a log window without a message pump.
			 Used in window_class_mt.hpp for logging messages
			 from a display window.

****************************************************************/



#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"

namespace window {

	class window_class_log_window : public log_window {
	public:
		window_class_log_window(const string& title);
		~window_class_log_window();

		// setup the window with no message pump
		errors::codes go() override;
	private:
		void window_settings() override;
		void create_window() override;
		string m_window_title;
		WNDCLASS m_wclw_wc = {};
		string m_class_name = READ_ONLY_STRING("window class log window");
		inline static std::atomic<ATOM> m_class_atm = 0;
	};
}