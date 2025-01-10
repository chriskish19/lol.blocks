#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// when you use this make sure to new allocate windows_string
class windows_string {
public:
	windows_string(const std::wstring& s) noexcept;
	~windows_string();
	LPCWSTR m_lpcws;
private:
	std::wstring* m_ws;
};
