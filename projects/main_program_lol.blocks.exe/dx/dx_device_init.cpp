#include "dx_device_init.hpp"

dx::devices_11::devices_11(UINT window_width, UINT window_height, HWND window_handle, const string& window_name)
:m_window_handle(window_handle),m_window_name(window_name){
#if ENABLE_ALL_EXCEPTIONS
	if (m_window_handle == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("m_window_handle"));
	}
#endif

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

	create_device();

	ID3D11Resource* back_buffer_p = nullptr;
	m_sc_p->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&back_buffer_p));
	m_device_p->CreateRenderTargetView(
		back_buffer_p,
		nullptr,
		&m_render_target_p
	);
	back_buffer_p->Release();
}

dx::devices_11::~devices_11()
{
	if (m_feature_levels != nullptr) {
		delete[] m_feature_levels;
	}

	if (m_swap_chain_desc_p != nullptr) {
		delete m_swap_chain_desc_p;
	}

	if (m_device_context_p != nullptr) {
		m_device_context_p->Release();
	}

	if (m_device_p != nullptr) {
		m_device_p->Release();
	}

	if (m_sc_p != nullptr) {
		m_sc_p->Release();
	}

	if (m_render_target_p != nullptr) {
		m_render_target_p->Release();
	}
	
}

errors::codes dx::devices_11::create_device()
{
	HRESULT hr;

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
#if ENABLE_FULL_DEBUG
		D3D11_CREATE_DEVICE_DEBUG,
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

	if (SUCCEEDED(hr)) {
#if ENABLE_DEEP_LOGS
		global::log_to_system_log_window(m_window_name + READ_ONLY_STRING(":Direct3d11 device and swap chain created successfully!"));
#endif
	}
	else {
#if ENABLE_ALL_EXCEPTIONS
		throw errors::dx_error(hr);
#endif

#if ENABLE_DEEP_LOGS
		global::log_to_system_log_window(m_window_name + READ_ONLY_STRING(":Direct3d11 device and swap chain failure!"));
#endif
	}

	return errors::codes::success;
}
