#ifndef LOL_BLOCKS_SINGLETONS_HEADER_HPP
#define LOL_BLOCKS_SINGLETONS_HEADER_HPP

// include win32gui
#include "win32gui.include/win32gui.include.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class_mt.hpp"

namespace main_lol_blocks_exe {
	extern window_manager* m_public_window_manager;
	extern window_class_mt* m_public_window_class_mt;
}

namespace utilities {
	void clean_up_destructor() noexcept;
}


// LOL_BLOCKS_SINGLETONS_HEADER_HPP
#endif