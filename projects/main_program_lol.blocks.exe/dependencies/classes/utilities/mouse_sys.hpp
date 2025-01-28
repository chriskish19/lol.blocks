/****************************************************************
	Header: mouse_sys.hpp

	Purpose: handle mouse movement and button presses between 
			 the window and graphics logic.

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
	class mouse {
	public:
		mouse() = default;

		enum class mouse_buttons {
			left_click,
			right_click,
			scroll_wheel,
		};

		class mouse_event {
		public:
			mouse_event();

			HWND get_window_handle() { return m_mouse_window_handle; }
			POINT get_mouse_position() { return m_pt; }
			mouse_buttons get_mouse_button() { return m_mb; }
		private:
			HWND m_mouse_window_handle = nullptr;
			POINT m_pt = {};
			mouse_buttons m_mb;
		};

		errors::codes add_mouse_event(const mouse_event& me);
		errors::codes system_message_handler();
	private:
		std::queue<mouse_event> m_me_queue;

	};
}