#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

namespace main {
	inline void go() {
		// global logging window messages throughout whole program
		std::thread lw_thread(&window::log_window::go, global::log_window_p);

		// main thread runs all here
		window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
		local_window_mt_system_p->go();
		







		local_window_mt_system_p->wait();
		if (local_window_mt_system_p != nullptr) {
			delete local_window_mt_system_p;
		}

		// log window can stay open to show possible errors
		if (lw_thread.joinable()) {
			lw_thread.join();
		}
		


		global::clean_up();
	}
}

// GO_HPP
#endif