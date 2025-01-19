#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/starter.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"

namespace window {
	class log_window :
		public starter{
	
	public:
		log_window();

		void go();
	private:
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		
		void message_pump() override;

		
	};
}