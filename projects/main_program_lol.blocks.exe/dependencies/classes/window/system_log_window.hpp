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
	class system_log_window : public log_window {
	public:
		system_log_window() = default;

		// setup the window and run message pump
		errors::codes go() override;

	private:

	};
}