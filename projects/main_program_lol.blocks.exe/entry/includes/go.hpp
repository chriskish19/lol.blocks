#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

namespace main {
	inline void go() {
		// main thread runs all here
		window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
		local_window_mt_system_p->go();
		window::log_window* local_log_window = new window::log_window;
		std::thread lw_thread(&window::log_window::go, local_log_window);







		local_window_mt_system_p->wait();
		if (local_window_mt_system_p != nullptr) {
			delete local_window_mt_system_p;
		}

		// log window can stay open beyond
		if (lw_thread.joinable()) {
			lw_thread.join();
		}
		
		if (local_log_window != nullptr) {
			delete local_log_window;
		}

	}
}

// GO_HPP
#endif