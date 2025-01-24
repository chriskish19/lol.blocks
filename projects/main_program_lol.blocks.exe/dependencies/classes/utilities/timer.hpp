#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// direct x api
#include "main_program_lol.blocks.exe/dependencies/dx_api/directx_includes.hpp"

// error codes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"

namespace utilities{
	class timer {
	public:
		timer() = default;

		// UINT seconds();
		UINT milliseconds();
	private:
		void interval();

		UINT m_delta_ms = 0;
		UINT m_delta_s = 0;

		std::chrono::system_clock::time_point m_t1,m_t2;
		bool m_interval_check = false;
	};
}