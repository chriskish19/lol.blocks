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

// dx dependencies
#include "main_program_lol.blocks.exe/dx/dx_device_init.hpp"


namespace dx {
	class draw : public devices_11 {
	public:
		draw(UINT window_width, UINT window_height, HWND window_handle);

		errors::codes triangle();
		errors::codes cube();
		errors::codes clear_buffer(float red, float green, float blue);
		
	private:
		
		errors::codes compile_shaders();

		struct vertex {
			UINT x;
			UINT y;
		};

	};
}