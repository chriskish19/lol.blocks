/****************************************************************
	Header: draw.hpp

	Purpose: this header is to test drawing shapes.

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

// dx dependencies
#include "main_program_lol.blocks.exe/dx/dx_device_init.hpp"


namespace dx {
	class draw : public devices_11 {
	public:
		draw(UINT window_width, UINT window_height, HWND window_handle, const string& window_name);
		~draw();

		errors::codes render_triangle();
		errors::codes render_cube();
	
		errors::codes clear_buffer(float red, float green, float blue);
		
		errors::codes ready_triangle();
		errors::codes ready_cube();
	private:
		class triangle {
		public:
			triangle(UINT window_width, UINT window_height);
			~triangle();

			ID3D11InputLayout* m_il_p = nullptr;

			D3D11_SUBRESOURCE_DATA* m_vertex_sub_data_p = nullptr;

			D3D11_BUFFER_DESC* m_vertex_buffer_desc_p = nullptr;
			ID3D11Buffer* m_vertex_buffer_p = nullptr;

			ID3D11VertexShader* m_vs_p = nullptr;
			ID3D11PixelShader* m_ps_p = nullptr;

			ID3DBlob* m_vs_blob = nullptr;
			ID3DBlob* m_ps_blob = nullptr;

			struct vertex {
				float x;
				float y;
			};

			const vertex m_vertices[3] = {
					{ 0.0f,  0.5f},
					{ 0.5f, -0.5f},
					{-0.5f, -0.5f}
			};

			const UINT* m_stride = new UINT(sizeof(vertex));
			const UINT* m_offset = new UINT(0u);

			D3D11_VIEWPORT* m_view_desc_p = nullptr;
			D3D11_INPUT_ELEMENT_DESC* m_ied_p = nullptr;
		};

		class cube {
		public:
			cube(UINT window_width, UINT window_height);
			~cube();

			
			ID3D11InputLayout* m_il_p = nullptr;

			D3D11_SUBRESOURCE_DATA* m_sub_data_p = nullptr;

			D3D11_BUFFER_DESC* m_buffer_desc_p = nullptr;
			ID3D11Buffer* m_buffer_p = nullptr;

			ID3D11Buffer* m_index_buffer_p = nullptr;

			ID3D11VertexShader* m_vs_p = nullptr;
			ID3D11PixelShader* m_ps_p = nullptr;

			ID3DBlob* m_vs_blob = nullptr;
			ID3DBlob* m_ps_blob = nullptr;

			struct vertex {
				float x, y, z;
			};

			UINT* m_indices = nullptr;
			vertex* m_vertices = nullptr;
			const UINT* m_stride = new UINT(sizeof(vertex));
			const UINT* m_offset = new UINT(0u);

			D3D11_VIEWPORT* m_view_desc_p = nullptr;
			D3D11_INPUT_ELEMENT_DESC* m_ied_p = nullptr;
		};
		
		cube* m_cube_p = nullptr;
		triangle* m_tri_p = nullptr;

		errors::codes create_buffer(triangle* tri_p);
		errors::codes create_buffer(cube* cube_p);

		errors::codes create_vertex_shader(ID3D11VertexShader** vs_pp, ID3DBlob** vs_blob_pp);
		errors::codes create_pixel_shader(ID3D11PixelShader** ps_pp, ID3DBlob** ps_blob_pp);
		errors::codes compile_shaders(std::filesystem::path shader_fp, ID3DBlob** shader_blob_pp, LPCSTR target_profile);
	};
}