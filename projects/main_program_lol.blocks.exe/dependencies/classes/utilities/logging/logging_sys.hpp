#ifndef LOGGING_SYSTEM_HEADER_HPP
#define LOGGING_SYSTEM_HEADER_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

namespace utilities {
	class log_info {
	public:
		log_info() = default;
		
	private:
		std::wstring get_last_error_win32() noexcept;
		std::wstring get_last_error_lol_blocks() noexcept;
	};
}



// LOGGING_SYSTEM_HEADER_HPP
#endif