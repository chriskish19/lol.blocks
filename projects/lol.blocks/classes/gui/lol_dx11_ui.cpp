#include "lol_dx11_ui.hpp"
#include NAMES_INCLUDE
#include DX11UI_INCLUDE_PATH

dx11::triangle_demo::triangle_demo(HWND handle,UINT width, UINT height)
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

dx11::triangle_demo::~triangle_demo()
{
	if (m_p_dd != nullptr) {
		delete m_p_dd;
		m_p_dd = nullptr;
	}

	if (m_p_rtv != nullptr) {
		m_p_rtv->Release();
	}

	if (m_il != nullptr) {
		m_il->Release();
	}

	if (m_sc_ps != nullptr) {
		m_sc_ps->Release();
	}

	if (m_sc_vs != nullptr) {
		m_sc_vs->Release();
	}

	if (m_vsb != nullptr) {
		m_vsb->Release();
	}

	if (m_vb != nullptr) {
		m_vb->Release();
	}
}

lb::codes dx11::triangle_demo::load_content()
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef DX11_DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif


	/*
	
	HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);
	
	*/


	{
		ID3DBlob* eb = nullptr; // error buffer
		HRESULT hr;
		hr = D3DCompileFromFile(
			TDDX11VS_FILE_PATH, 
			nullptr, 
			nullptr, 
			"VS_Main", 
			"vs_4_0",
			shaderFlags,
			0, 
			&m_vsb, 
			&eb
		);


		st_vs_out(hr);
		if (FAILED(hr)) {
			lb::codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			lb::output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return lb::codes::dx_error;
		}
	}
	
	// create vertex shader
	{
		/*
		
					HRESULT CreateVertexShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11VertexShader **ppVertexShader
			);
		
		*/
		
		
		HRESULT hr = m_p_dd->pDevice->CreateVertexShader(
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			nullptr,
			&m_sc_vs
		);

		st_vs_out(hr);
		if (FAILED(hr)) {
			return lb::codes::dx_error;
		}
	}

	// vertex layout
	D3D11_INPUT_ELEMENT_DESC vl[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
						D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	// number of elements in vertex layout
	UINT no_vl_e = std::size(vl);

	/*
	
			HRESULT CreateInputLayout(
		  [in]            const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
		  [in]            UINT                           NumElements,
		  [in]            const void                     *pShaderBytecodeWithInputSignature,
		  [in]            SIZE_T                         BytecodeLength,
		  [out, optional] ID3D11InputLayout              **ppInputLayout
		);
	
	*/

	{
		HRESULT hr = m_p_dd->pDevice->CreateInputLayout(
			vl,
			no_vl_e,
			m_vsb->GetBufferPointer(),
			m_vsb->GetBufferSize(),
			&m_il
		);

		st_vs_out(hr);
		if (FAILED(hr)) {
			return lb::codes::dx_error;
		}
	}

	// compile pixel shader
	{
		/*
		
		HRESULT D3DCompileFromFile(
		  [in]            LPCWSTR                pFileName,
		  [in, optional]  const D3D_SHADER_MACRO *pDefines,
		  [in, optional]  ID3DInclude            *pInclude,
		  [in]            LPCSTR                 pEntrypoint,
		  [in]            LPCSTR                 pTarget,
		  [in]            UINT                   Flags1,
		  [in]            UINT                   Flags2,
		  [out]           ID3DBlob               **ppCode,
		  [out, optional] ID3DBlob               **ppErrorMsgs
		);
	
		
		*/
		
		
		// error buffer
		ID3DBlob* eb = nullptr;

		HRESULT hr = D3DCompileFromFile(
			TDDX11PS_FILE_PATH,
			nullptr,
			nullptr,
			"PS_Main",
			"ps_4_0",
			shaderFlags,
			0,
			&m_psb,
			&eb
		);

		st_vs_out(hr);
		if (FAILED(hr)) {
			lb::codes code;

			// compile error string
			string ce = error_blob_ts(eb, &code);
			lb::output_code(code);

			OutputDebugString(ce.c_str());
		}

		if (eb != nullptr) {
			eb->Release();
			return lb::codes::dx_error;
		}
	

	}


	// create pixel shader
	{
		/*
		
					HRESULT CreatePixelShader(
			  [in]            const void         *pShaderBytecode,
			  [in]            SIZE_T             BytecodeLength,
			  [in, optional]  ID3D11ClassLinkage *pClassLinkage,
			  [out, optional] ID3D11PixelShader  **ppPixelShader
			);
		
		*/
		
		
		HRESULT hr = m_p_dd->pDevice->CreatePixelShader(
			m_psb->GetBufferPointer(),
			m_psb->GetBufferSize(),
			nullptr,
			&m_sc_ps
		);

		st_vs_out(hr);
		if (FAILED(hr)) {
			return lb::codes::dx_error;
		}

	}



	VertexPos vertices[]
	{
		DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 3;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = vertices;

	// create vertex buffer
	{
		HRESULT hr = m_p_dd->pDevice->CreateBuffer(
			&vertexDesc,
			&resourceData,
			&m_vb
		);

		st_vs_out(hr);
		if (FAILED(hr)) {
			return lb::codes::dx_error;
		}

	}

	{
		
	}


	return lb::codes::success;
}

void dx11::triangle_demo::unload_content()
{

}

void dx11::triangle_demo::update(float dt)
{

}

void dx11::triangle_demo::render()
{
	if (m_p_dd->pImmediateContext == 0)
		return;
	
	float clear_color[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

	m_p_dd->pImmediateContext->ClearRenderTargetView(m_p_rtv, clear_color);

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;


	m_p_dd->pImmediateContext->IASetInputLayout(m_il);
	m_p_dd->pImmediateContext->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
	m_p_dd->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_p_dd->pImmediateContext->VSSetShader(m_sc_vs, 0, 0);
	m_p_dd->pImmediateContext->PSSetShader(m_sc_ps, 0, 0);
	m_p_dd->pImmediateContext->Draw(3, 0);



	m_p_dd->pSwapChain->Present(0, 0);
}

dx11::texture_demo::texture_demo(HWND handle, UINT width, UINT height)
{
}

dx11::texture_demo::~texture_demo()
{
}

lb::codes dx11::texture_demo::load_content()
{
	return lb::codes();
}

void dx11::texture_demo::unload_content()
{
}

void dx11::texture_demo::update(float dt)
{
}

void dx11::texture_demo::render()
{
}
