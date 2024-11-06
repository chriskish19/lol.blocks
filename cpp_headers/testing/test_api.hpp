#pragma once


// includes everything! 
// which means the test api is only meant to run from main.cpp
// and is not part of the pch
#include "pch/lol.PCH.hpp" 


// this is where we write bad code! the test api isnt pretty
namespace TEST_API {
	// simple functions used to test exceptions
	// they all throw
	lolblock_ec for_loop_count();
	lolblock_ec vector_adding();
	lolblock_ec map_find();





	// creates template objects
	lolblock_ec standard_init_templates();



}