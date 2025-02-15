/****************************************************************
	Header: go.hpp

	Purpose: keep main.cpp clean.

****************************************************************/


#ifndef GO_HPP
#define GO_HPP

#include "main_program_lol.blocks.exe/pch/pch.hpp"

namespace main {
	// main go function to run whole program
	errors::any_two<errors::codes, errors::win32_codes> go();

	// draw function
	errors::any_two<errors::codes,errors::win32_codes> draw();

	void shutdown();
}

// GO_HPP
#endif