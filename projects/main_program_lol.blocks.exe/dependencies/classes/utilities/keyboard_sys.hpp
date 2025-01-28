/****************************************************************
	Header: keyboard_sys.hpp

	Purpose: handles keystrokes between the window and graphics
			 logic.

****************************************************************/



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

namespace utilities {
	class keyboard {
	public:
		keyboard() = default;

		enum class em_key_state {
			released,
			pressed
		};

		class key_event {
		public:
			char key;
			em_key_state state;
		};

		errors::codes add_event(key_event kp);

		// run this in the graphics logic??
		errors::codes system_message_handler();
	private:
		std::queue<key_event> m_key_queue;
	};
}