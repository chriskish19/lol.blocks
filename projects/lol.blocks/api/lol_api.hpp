/****************************************************************
*	Header: lol.api.hpp
*
*	Purpose: helper functions 
*
****************************************************************/


#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include CODEOBJECT_INCLUDE_PATH
#include DESCRIPTION_INCLUDE_PATH
#include SHAPES_INCLUDE_PATH

namespace lol_blocks_api {
	// string conversions, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);

	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	std::wstring to_wide_string(const char* narrow,lb::codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, lb::codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, lb::codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, lb::codes* code_p);

	// win32 functions
	UINT get_window_width(HWND window_handle);
	UINT get_window_height(HWND window_handle);


	// simple drawing functions
	lb::cube create_cube(lb::size sz,lb::position p);					// create a cube from a position and size
	std::vector<DirectX::XMFLOAT3> cube_to_vb(const lb::cube& cb);		// cube to vertex buffer, organizes a cube to be read as a vertex buffer

}