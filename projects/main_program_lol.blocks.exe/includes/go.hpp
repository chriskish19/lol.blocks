#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

using namespace utilities;

namespace main_lol_blocks_exe {
	inline void go() {
		// all singletons used in the program
		singleton_manager* manage_the_singleton_objects = singleton_manager::get_singleton_manager();

		


		

		// clean up main singleton object
		delete manage_the_singleton_objects;
	}
}

// GO_HPP
#endif

/*

		// launch a thread to run the main window logic
		std::function<void(window_create*)> run_main_window_logic_loop_function = function_name;
		manage_the_singleton_objects->m_tm->create_new_thread
			(
				run_main_window_logic_loop_function,
				manage_the_singleton_objects->m_wc
			);

*/