#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

// set in "debug_settings.hpp" check "pch.hpp"
#if USE_MAIN_ENTRY_CPP

using namespace main_lol_blocks_exe;
using namespace utilities;


/*  unicode is defined with cmake!
#ifndef UNICODE
#define UNICODE 
#endif // !UNICODE
*/

// handles most running of program
#include "main_program_lol.blocks.exe/includes/go.hpp"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	// main thread runs all here
	m_public_window_class_mt->go();

	{
		// wait here
		std::mutex local_mtx;
		std::unique_lock<std::mutex> local_lock(local_mtx);
		m_public_safe_exit->wait(local_lock, []
			{
				return m_public_safe_exit_gate_latch->load();
			});
	}



	// clean up main singleton object
	utilities::clean_up_destructor();

	// win32 api specific return code
	return NULL;
}


// USE TEST API ENTRY POINT
#elif USE_TEST_API

#include "main_program_lol.blocks.exe/testing/test_api.hpp

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
