/****************************************************************
	Header: xxxxxx

	Purpose: xxxxx

****************************************************************/

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// classes
#include "main_program_lol.blocks.exe/classes/window/pieces/starter.hpp"


namespace window {
	class a_window : public starter{
	public:
		a_window() = default;

		a_window(const string& title);

		UINT width();
		UINT height();

		HWND handle() { return m_window_handle; }

	};
}