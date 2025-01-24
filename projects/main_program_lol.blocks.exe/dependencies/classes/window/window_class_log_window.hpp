#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"


namespace window {
	class window_class_log_window : public log_window {
	public:
		window_class_log_window(const string& title);

		// setup the window with no message pump
		errors::codes go() override;
		void create_window() override;
	private:
		string m_window_title;
	};
}