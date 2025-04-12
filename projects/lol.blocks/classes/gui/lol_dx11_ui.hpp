/***********************************************
* File: lol_dx11_ui.hpp ( direct x 11 user interface)
*
* Purpose: 
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
	class demo {
	public:
		demo(HWND handle,UINT width, UINT height);
		~demo();


		lb::codes load_content();
		void unload_content();
		void update(float dt);
		void render();

		std::vector<lb::codes> get_demo_codes_init_vec() { return m_codes_v; }
	protected:
		std::vector<lb::codes> m_codes_v;

		device_description* m_p_dd = new device_description{};
		
		ID3D11RenderTargetView* m_p_rtv = nullptr;
	};
}