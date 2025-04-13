#include NAMES_INCLUDE
#include DX11UI_INCLUDE_PATH

dx11::demo::demo(HWND handle,UINT width, UINT height)
{
	
	// driver types
	std::vector<D3D_DRIVER_TYPE> local_dt_v =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};
	
	
	// feature levels
	std::vector<D3D_FEATURE_LEVEL>* fl = new std::vector<D3D_FEATURE_LEVEL>
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// set the pointer
	m_p_dd->pFeatureLevels = fl->data();

	// set the number of feature levels
	m_p_dd->FeatureLevels = fl->size();


	// swap chain description
	DXGI_SWAP_CHAIN_DESC local_scd = {};
	local_scd.BufferCount = 1;
	local_scd.BufferDesc.Width = width;
	local_scd.BufferDesc.Height = height;
	local_scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	local_scd.BufferDesc.RefreshRate.Numerator = 60;
	local_scd.BufferDesc.RefreshRate.Denominator = 1;
	local_scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	local_scd.OutputWindow = handle;
	local_scd.Windowed = true;
	local_scd.SampleDesc.Count = 1;
	local_scd.SampleDesc.Quality = 0;
	
	// creation flags
	unsigned int cf = 0;
#ifdef DX11_DEBUG
	cf |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	m_p_dd->Flags = cf;
	m_p_dd->pSwapChainDesc = new DXGI_SWAP_CHAIN_DESC(local_scd);
	m_p_dd->SDKVersion = D3D11_SDK_VERSION;

	for (auto type : local_dt_v) {
		m_p_dd->DriverType = type;
		HRESULT code = create_device(m_p_dd);
		if (SUCCEEDED(code)) {
			break;
		}
	}


	// create back buffer
	ID3D11Texture2D* p_bb = nullptr;
	p_bb = cbb(m_p_dd->pSwapChain);
	

	// create rtv
	ID3D11RenderTargetView* p_rtv = nullptr;
	p_rtv = crtv(m_p_dd->pDevice, p_bb);
	
	m_p_rtv = p_rtv;

	if (p_bb != nullptr) {
		p_bb->Release();
	}


	m_p_dd->pImmediateContext->OMSetRenderTargets(1, &p_rtv, 0);

	// view port description
	D3D11_VIEWPORT local_vp = {};
	local_vp.Width = static_cast<float>(width);
	local_vp.Height = static_cast<float>(height);
	local_vp.MinDepth = 0.0f;
	local_vp.MaxDepth = 1.0f;
	local_vp.TopLeftX = 0.0f;
	local_vp.TopLeftY = 0.0f;


	m_p_dd->pImmediateContext->RSSetViewports(1, &local_vp);

}

dx11::demo::~demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}
}

lb::codes dx11::demo::load_content()
{
	return lb::codes();
}

void dx11::demo::unload_content()
{

}

void dx11::demo::update(float dt)
{

}

void dx11::demo::render()
{
	if (m_p_dd->pImmediateContext == 0)
		return;
	
	float clear_color[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clear_color);
	m_p_dd->pSwapChain->Present(0, 0);
}
