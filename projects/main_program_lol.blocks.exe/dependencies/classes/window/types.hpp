#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// global variables
#include "main_program_lol.blocks.exe/dependencies/global/globals.hpp"


class windows_string {
public:
	windows_string(const std::wstring& s) noexcept;
	LPCWSTR get_raw_p() noexcept { return m_lpcws; }
private:
	std::wstring m_ws;
	LPCWSTR m_lpcws;
};
