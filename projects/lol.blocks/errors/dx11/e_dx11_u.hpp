/***********************************************
* File: e_dx11_u.hpp (errors direct x 11 utilities)
*
* Purpose: helper functions for dx11 errors
*
* Used: within the dx11 namespace
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include CODE_UTILITIES_INCLUDE_PATH

namespace dx11 {
	// translate a ID3D11InfoQueue* to a string
	string debug_info_ts(ID3D11InfoQueue* debug_info_p, lol_blocks::codes* code);

	// translate a blob error to string
	string error_blob_ts(ID3DBlob* error, lol_blocks::codes* code);

	// translate an hresult code to a string 
	string hr_ts(HRESULT hr);

	// send to visual studio output window
	void st_vs_out(HRESULT hr);
}