#include "macros/include/lol.blocks.macro_guard.include.hpp"

// set in LOL_BLOCKS_SYSTEM_DEBUG_MACROS.hpp
#if USE_MAIN_ENTRY_CPP

#include "pch/include/main_pch.hpp"

using namespace main_lol_blocks_exe;
using namespace utilities;


/*  unicode is defined with cmake!
#ifndef UNICODE
#define UNICODE 
#endif // !UNICODE
*/

void run_main_window_logic_loop(window_create* main_window) {

	while (main_window->m_public_p_running_logic->load()) {
		// graphics logic here for main window
	}
}


int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
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

	// win32 api specific return code
	return NULL;
}



// USE TEST API ENTRY POINT
#elif USE_TEST_API


#include "testing/test_api.hpp"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {

	// run test api here...

	return NULL;
}

// USE_MAIN_ENTRY_CPP
#endif
