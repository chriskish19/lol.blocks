#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

using namespace utilities;

namespace main_lol_blocks_exe {
	inline void go() {
		// all singletons used in the program
		singleton_manager* manage_the_singleton_objects = singleton_manager::get_singleton_manager();

		// main thread runs all here
		manage_the_singleton_objects->m_wc_mt->go();

		// clean up main singleton object
		delete manage_the_singleton_objects;
	}
}

// GO_HPP
#endif