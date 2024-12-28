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
	// run!
	go();

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
