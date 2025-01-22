#include "dx_device_init.hpp"

dx::devices_11::devices_11(UINT window_width, UINT window_height, HWND window_handle) 
:m_window_handle(window_handle){


	m_feature_levels = new D3D_FEATURE_LEVEL[]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	DXGI_MODE_DESC mode_desc = {
		window_width,
		window_height,
		DXGI_RATIONAL{0,0},
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING_UNSPECIFIED,
	};


	m_swap_chain_desc_p = new DXGI_SWAP_CHAIN_DESC{
		mode_desc,
		DXGI_SAMPLE_DESC{1,0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		1u,
		m_window_handle,
		TRUE,
		DXGI_SWAP_EFFECT_DISCARD,
		0u
	};
}

errors::codes dx::devices_11::create_device()
{
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
#if ENABLE_FULL_DEBUG
		D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE,
#endif

#if ENABLE_FULL_OPTIMIZATIONS
		0u,
#endif
		m_feature_levels,
		m_feature_levels_count,
		D3D11_SDK_VERSION,
		m_swap_chain_desc_p,
		&m_sc_p,
		&m_device_p,
		nullptr,
		&m_device_context_p
	);


}
