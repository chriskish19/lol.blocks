#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

namespace main {
	inline void go() {
		// main thread runs all here
		window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
		local_window_mt_system_p->go();
		







		local_window_mt_system_p->wait();
		if (local_window_mt_system_p != nullptr) {
			delete local_window_mt_system_p;
		}
	}
}

// GO_HPP
#endif