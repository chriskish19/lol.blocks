#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

namespace main_lol_blocks_exe {
	inline void go() {
		// main thread runs all here
		singletons::global_window_class_mt_p->go();

		{
			// wait here
			std::mutex local_mtx;
			std::unique_lock<std::mutex> local_lock(local_mtx);
			global_safe_exit_p->wait(local_lock, []
				{
					return global_safe_exit_gate_latch_p->load();
				});
		}

		main_lol_blocks_exe::clean_up_globals();
		singletons::clean_up_singles();
	}
}

// GO_HPP
#endif