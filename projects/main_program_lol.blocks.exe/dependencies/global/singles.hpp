#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class_mt.hpp"

namespace singletons {
	extern main_lol_blocks_exe::window_manager* global_window_manager_p;
	extern main_lol_blocks_exe::window_class_mt* global_window_class_mt_p;

	void clean_up_singles() noexcept;
}