/****************************************************************
	Header: go.hpp

	Purpose: keep main.cpp clean.

****************************************************************/



#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/pch/pch.hpp"

namespace main {
	// main thread runs all here
	inline void go() {
		// global logging window messages throughout whole program
		std::thread lw_thread(&window::log_window::go, global::log_window_p->load());

		// main window class
		window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
		local_window_mt_system_p->go();
		

		// waits until all display windows are closed
		local_window_mt_system_p->wait();
		global::log_window_p->load()->set_all_display_windows_closed(true);
		global::all_display_windows_closed->store(global::log_window_p->load()->get_all_display_windows_closed());
		global::log_window_p->load()->add_x_log_window();
		if (local_window_mt_system_p != nullptr) {
			delete local_window_mt_system_p;
		}

		// a message sent to the system log window
		global::log_to_system_log_window(READ_ONLY_STRING("All display windows closed. Close this window to exit program."));

		// system log window can stay open to show possible errors
		if (lw_thread.joinable()) {
			lw_thread.join();
		}
		
		// deletes all global objects
		global::clean_up();
	}
}

// GO_HPP
#endif