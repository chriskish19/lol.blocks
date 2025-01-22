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

namespace dx {
	class devices_11 {
	public:
		devices_11(UINT window_width, UINT window_height, HWND window_handle);

		~devices_11();
	private:
		errors::codes create_device();

		IDXGISwapChain* m_sc_p = nullptr;
		ID3D11Device* m_device_p = nullptr;
		ID3D11DeviceContext* m_device_context_p = nullptr;
		const D3D_FEATURE_LEVEL* m_feature_levels = nullptr;
		size_t m_feature_levels_count = 6;
		const DXGI_SWAP_CHAIN_DESC* m_swap_chain_desc_p = nullptr;
		HWND m_window_handle = nullptr;
	};
}