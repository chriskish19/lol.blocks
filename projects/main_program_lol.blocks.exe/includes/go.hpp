#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

namespace main_lol_blocks_exe {
	inline void go() {
		// main thread runs all here
		window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
		local_window_mt_system_p->go();

		{
			// wait here
			std::mutex local_mtx;
			std::unique_lock<std::mutex> local_lock(local_mtx);
			local_window_mt_system_p->m_wcmt_latches->m_safe_exit.wait(local_lock, [local_window_mt_system_p]
				{
					return local_window_mt_system_p->m_wcmt_latches->m_safe_exit_gate_latch.load();
				});
		}

		if (local_window_mt_system_p != nullptr) {
			delete local_window_mt_system_p;
		}

	}
}

// GO_HPP
#endif