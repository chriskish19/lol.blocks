/****************************************************************
	Header: test.api.hpp

	Purpose: runs tests

****************************************************************/

#pragma once

// include all
#include "main_program_lol.blocks.exe/pch/pch.hpp"

// dx11 tests
#include "main_program_lol.blocks.exe/testing/dx11/draw.hpp"

// window
#include "main_program_lol.blocks.exe\testing\window\window_test.hpp"

namespace testing {
	void handle_basic_error_codes(errors::codes code, const string& location = errors::get_location()) noexcept;

	errors::codes create_windows(size_t number_of_open_windows);
	errors::codes draw_shapes(draw* p_draw, window::log_window* log_p);
	errors::codes string_conversions(const std::string& narrow_test);
	errors::codes string_conversions_file(const std::filesystem::path& p);
	errors::codes window_logger();
}