#pragma once
#include "testing/pch/testing.lol.PCH.hpp" // this includes everything in the main project (lol.blocks.exe)


namespace TEST_API {
	// simple functions used to test exceptions
	// they all throw
	lolblock_ec for_loop_count();
	lolblock_ec vector_adding();
	lolblock_ec map_find();





	// creates template objects
	lolblock_ec standard_init_templates();



}