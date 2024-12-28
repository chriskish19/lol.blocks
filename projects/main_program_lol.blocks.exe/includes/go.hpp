#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

using namespace utilities;

namespace main_lol_blocks_exe {
	inline void run_main_window_logic_loop(window_create* main_window) {

		while (main_window->m_public_p_running_logic->load()) {
			// graphics logic here for main window
		}
	}


	inline void go() {
		// keeping the stack happy
		window_create* main_app_p = new window_create(L"main window,lol.blocks");

		// launch a thread to run the main window logic
		std::thread main_window_logic_thread(&run_main_window_logic_loop, main_app_p);

		// Run the main thread message loop.
		MSG msg = { };
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// shutdown run_main_window_logic_loop(...)
		main_app_p->m_public_p_running_logic->store(false);
		main_window_logic_thread.join();

		// check open window count before main thread exits
		// if open window count equals zero it is safe to exit.
		std::unique_lock<std::mutex> lock(main_app_p->m_public_mtx_open_window_count);
		bool exit = true;

		while (exit) {

			// main thread checks open window count each time a window is closed
			if (main_app_p->get_open_window_count() == 0) {
				// set while loop to condition to false and exit
				exit = false;
			}
			else {
				main_app_p->m_public_cv_open_window_count.wait(lock, [main_app_p] { return main_app_p->m_public_open_window_count_gate_state.load(); });
			}

			// close the gate and check agian later
			main_app_p->m_public_open_window_count_gate_state = false;
		}

		// clean up main application object
		delete main_app_p;
	}
}

// GO_HPP
#endif