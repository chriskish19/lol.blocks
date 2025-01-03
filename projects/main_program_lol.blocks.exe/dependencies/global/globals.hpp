#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

namespace main_lol_blocks_exe {
	extern std::condition_variable* global_safe_exit_p;
	extern std::atomic<bool>* global_safe_exit_gate_latch_p;
	extern std::condition_variable* global_window_create_signaler_p;
	extern std::atomic<bool>* global_new_window_gate_latch_p;
	

	void clean_up_globals() noexcept;
}