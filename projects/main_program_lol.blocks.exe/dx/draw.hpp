// this header is to test drawing shapes and nothing more

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
		draw(UINT window_width, UINT window_height, HWND window_handle, const string& window_name);
		~draw();

		errors::codes triangle();
		errors::codes cube();
		errors::codes clear_buffer(float red, float green, float blue);
		
	private:
		ID3D11VertexShader* m_vs_p = nullptr;
		ID3D11PixelShader* m_ps_p = nullptr;

		ID3DBlob* m_vs_blob = nullptr;
		ID3DBlob* m_ps_blob = nullptr;

		errors::codes create_vertex_shader(ID3D11VertexShader* vs_p, ID3DBlob* vs_blob);
		errors::codes create_pixel_shader(ID3D11PixelShader* ps_p, ID3DBlob* ps_blob);
		errors::codes compile_shaders(std::filesystem::path shader_fp, ID3DBlob* shader_blob,ID3DBlob* error);

		struct vertex {
			UINT x;
			UINT y;
		};

	};
}