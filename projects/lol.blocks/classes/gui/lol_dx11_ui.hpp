/***********************************************
* File: lol_dx11_ui.hpp ( direct x 11 user interface)
*
* Purpose: render graphics to the screen
*
* Used: 
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include EDX11U_INCLUDE_PATH
#include DX11SETUP_INCLUDE_PATH



namespace dx11 {
	
	// renders a single triangle
	class triangle_demo {
	public:
		triangle_demo(HWND handle,UINT width, UINT height);
		~triangle_demo();


		lb::codes load_content();
		void unload_content();
		void update(float dt);
		void render();

		
	protected:
		// solid color vertex shader
		ID3D11VertexShader* m_sc_vs = nullptr;

		// solid color pixel shader
		ID3D11PixelShader* m_sc_ps = nullptr;

		// input layout
		ID3D11InputLayout* m_il = nullptr;

		// vertex buffer blob
		ID3DBlob* m_vsb = nullptr;

		// main struct for dx11 pointers
		device_description* m_p_dd = new device_description{};
		
		// render target view
		ID3D11RenderTargetView* m_p_rtv = nullptr;

		// pixel shader blob
		ID3DBlob* m_psb = nullptr;


		struct VertexPos
		{
			DirectX::XMFLOAT3 pos;
		};

		// vertex buffer
		ID3D11Buffer* m_vb = nullptr;
	};



	// renders a texture to the screen
	class texture_demo {
	public:
		texture_demo(HWND handle, UINT width, UINT height);
		~texture_demo();
		
		lb::codes load_content();
		void unload_content();
		void update(float dt);
		void render();



	protected:
		// solid color vertex shader
		ID3D11VertexShader* m_sc_vs = nullptr;

		// solid color pixel shader
		ID3D11PixelShader* m_sc_ps = nullptr;

		// input layout
		ID3D11InputLayout* m_il = nullptr;

		// vertex buffer blob
		ID3DBlob* m_vsb = nullptr;

		// main struct for dx11 pointers
		device_description* m_p_dd = new device_description{};

		// render target view
		ID3D11RenderTargetView* m_p_rtv = nullptr;

		// pixel shader blob
		ID3DBlob* m_psb = nullptr;

		// vertex buffer
		ID3D11Buffer* m_vb = nullptr;

	};
}