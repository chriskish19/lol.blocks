// Testing framework for lol.blocks
// find bugs!!!

#ifndef TESTING_API_HPP
#define TESTING_API_HPP

// main pch
#include "pch/include/main_pch.hpp"

// win32 gui include
#include "gui_projects_dll/win32gui.include/win32gui.lib.include.hpp"


namespace test_api {
	// standard testing
	utilities::lolblock_ec for_loop_count();
	utilities::lolblock_ec vector_adding();
	utilities::lolblock_ec map_find();
	utilities::lolblock_ec standard_init_templates();

	// win32gui testing
	utilities::lolblock_ec win32gui_init_test();


}

// TESTING_API_HPP
#endif