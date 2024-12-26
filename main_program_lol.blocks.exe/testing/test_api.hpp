// Testing framework for lol.blocks
// find bugs!!!

#ifndef TESTING_API_HPP
#define TESTING_API_HPP

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