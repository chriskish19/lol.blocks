#include "draw.hpp"

dx::draw::draw(UINT window_width, UINT window_height, HWND window_handle, const string& window_name)
	:devices_11(window_width, window_height, window_handle,window_name)
{
	m_tri_p = new triangle(window_width, window_height);
}

dx::draw::~draw()
{
	if (m_tri_p != nullptr) {
		delete m_tri_p;
	}
}

errors::codes dx::draw::draw_triangle()
{
	return errors::codes();
}

errors::codes dx::draw::draw_cube()
{
	return errors::codes();
}

errors::codes dx::draw::clear_buffer(float red, float green, float blue)
{
	const float color[] = {
		red,green,blue,1.0f
	};
	
	m_device_context_p->ClearRenderTargetView(m_render_target_p, color);
	
	return errors::codes::success;
}

errors::codes dx::draw::ready_triangle()
{
	// get exe path
	std::filesystem::path shader_dir = std::filesystem::current_path() / "shaders";

	std::filesystem::path vs_path = shader_dir / "vertex_shader.hlsl";
	std::filesystem::path ps_path = shader_dir / "pixel_shader.hlsl";

	// vertex shader
	compile_shaders(vs_path, m_tri_p->m_vs_blob, m_tri_p->m_error_blob);

	// pixel shader
	compile_shaders(ps_path, m_tri_p->m_ps_blob, m_tri_p->m_error_blob);
	
	
	create_vertex_shader(m_tri_p->m_vs_p, m_tri_p->m_vs_blob);
	create_pixel_shader(m_tri_p->m_ps_p, m_tri_p->m_ps_blob);
	create_buffer(m_tri_p);
	
	return errors::codes::success;
}

// TODO: finish this
errors::codes dx::draw::create_buffer(triangle* tri_p)
{
#if ENABLE_FULL_DEBUG

	if (tri_p == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (tri_p == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif



	{
		HRESULT hr;

		hr = m_device_p->CreateBuffer(tri_p->m_buffer_desc_p, tri_p->m_sub_data_p, &tri_p->m_buffer_p);

		if (FAILED(hr)) {

#if ENABLE_FULL_DEBUG

			errors::dx_error err(hr);
			errors::show_error_message_window(err.full_error_message(), err.get_code_string());

#endif

#if ENABLE_ALL_EXCEPTIONS

			throw errors::dx_error(hr);

#endif

		}
	}


	m_device_context_p->IASetVertexBuffers(0u, 1u, &tri_p->m_buffer_p, tri_p->m_stride, tri_p->m_offset);

	m_device_context_p->VSSetShader(tri_p->m_vs_p, nullptr, 0u);

	m_device_context_p->PSSetShader(tri_p->m_ps_p, nullptr, 0u);

	m_device_context_p->OMSetRenderTargets(1u, &m_render_target_p, nullptr);

	m_device_context_p->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_context_p->RSSetViewports(1u, tri_p->m_view_desc_p);

	m_device_context_p->Draw(std::size(tri_p->m_vertices), 0u);


	return errors::codes::success;
}

errors::codes dx::draw::create_buffer(cube* cube_p)
{
	return errors::codes();
}

errors::codes dx::draw::create_vertex_shader(ID3D11VertexShader* vs_p, ID3DBlob* vs_blob)
{

#if ENABLE_FULL_DEBUG

	if (vs_p == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}

	if (vs_blob == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (vs_p == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3D11VertexShader* vs_p"));
	}

	if (vs_blob == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif
	
	
	
	HRESULT hr;
	
	hr = m_device_p->CreateVertexShader(
		vs_blob->GetBufferPointer(),
		vs_blob->GetBufferSize(),
		nullptr,
		&vs_p
	);
	


#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		errors::dx_error create_vs_error(hr);
		errors::show_error_message_window(create_vs_error.full_error_message(), create_vs_error.get_code_string());
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		throw errors::dx_error(hr);
	}

#endif
	


	// the case where both exceptions and debug are disabled
	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}

	return errors::codes::success;
}

errors::codes dx::draw::create_pixel_shader(ID3D11PixelShader* ps_p, ID3DBlob* ps_blob)
{


#if ENABLE_FULL_DEBUG

	if (ps_p == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}

	if (ps_blob == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (ps_p == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3D11VertexShader* vs_p"));
	}

	if (ps_blob == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif



	HRESULT hr;

	hr = m_device_p->CreatePixelShader(
		ps_blob->GetBufferPointer(),
		ps_blob->GetBufferSize(),
		nullptr,
		&ps_p
	);



#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		errors::dx_error create_ps_error(hr);
		errors::show_error_message_window(create_ps_error.full_error_message(), create_ps_error.get_code_string());
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		throw errors::dx_error(hr);
	}

#endif



	// the case where both exceptions and debug are disabled
	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}

	return errors::codes::success;
	
	
	
}

errors::codes dx::draw::compile_shaders(std::filesystem::path shader_fp, ID3DBlob* shader_blob, ID3DBlob* error)
{	
	HRESULT hr;
	
	// Compile Vertex Shader
	hr = D3DCompileFromFile(
		shader_fp.c_str(),										// Filename
		nullptr,												// Optional macros
		nullptr,												// Optional include handler
		"main",													// Entry point
		"vs_5_0",												// Target profile
		
#if ENABLE_DX_DEBUG
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,		// Flags
#else
		D3DCOMPILE_OPTIMIZATION_LEVEL3,
#endif
		
		0,														// Additional flags
		&shader_blob,											// Compiled shader
		&error													// Errors
	);
	
#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		errors::dx_error err(hr, error);
		errors::show_error_message_window(err.full_error_message(), err.get_code_string());
	}

#endif

#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		throw errors::dx_error(hr, error);
	}

#endif

	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}
	return errors::codes::success;
}

dx::draw::triangle::triangle(UINT window_width, UINT window_height)
{
	/*

				typedef struct D3D11_BUFFER_DESC {
				  UINT        ByteWidth;
				  D3D11_USAGE Usage;
				  UINT        BindFlags;
				  UINT        CPUAccessFlags;
				  UINT        MiscFlags;
				  UINT        StructureByteStride;
				} D3D11_BUFFER_DESC;

				*/

	m_buffer_desc_p = new D3D11_BUFFER_DESC{
		sizeof(m_vertices),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		0u,
		0u,
		sizeof(vertex)
	};


	/*

	typedef struct D3D11_SUBRESOURCE_DATA {
		const void *pSysMem;
		UINT       SysMemPitch;
		UINT       SysMemSlicePitch;
	} D3D11_SUBRESOURCE_DATA;

	*/


	m_sub_data_p = new D3D11_SUBRESOURCE_DATA{
		m_vertices,
		0u,
		0u
	};

	/*

	typedef struct D3D11_VIEWPORT {
		FLOAT TopLeftX;
		FLOAT TopLeftY;
		FLOAT Width;
		FLOAT Height;
		FLOAT MinDepth;
		FLOAT MaxDepth;
	} D3D11_VIEWPORT;

	*/

	m_view_desc_p = new D3D11_VIEWPORT{
		0.0f,
		0.0f,
		(float)window_width,
		(float)window_height,
		0.0f,
		1.0f
	};

	/*

	typedef struct D3D11_INPUT_ELEMENT_DESC {
	  LPCSTR                     SemanticName;
	  UINT                       SemanticIndex;
	  DXGI_FORMAT                Format;
	  UINT                       InputSlot;
	  UINT                       AlignedByteOffset;
	  D3D11_INPUT_CLASSIFICATION InputSlotClass;
	  UINT                       InstanceDataStepRate;
	} D3D11_INPUT_ELEMENT_DESC;

	*/


}

dx::draw::triangle::~triangle()
{
	if (m_vs_p != nullptr) {
		m_vs_p->Release();
	}

	if (m_ps_p != nullptr) {
		m_ps_p->Release();
	}

	if (m_vs_blob != nullptr) {
		m_vs_blob->Release();
	}

	if (m_ps_blob != nullptr) {
		m_ps_blob->Release();
	}

	if (m_buffer_p != nullptr) {
		m_buffer_p->Release();
	}

	if (m_buffer_desc_p != nullptr) {
		delete m_buffer_desc_p;
	}

	if (m_sub_data_p != nullptr) {
		delete m_sub_data_p;
	}

	if (m_stride != nullptr) {
		delete m_stride;
	}

	if (m_offset != nullptr) {
		delete m_offset;
	}

	if (m_error_blob != nullptr) {
		delete m_error_blob;
	}

	if (m_il_p != nullptr) {
		delete m_il_p;
	}

	if (m_ied_p != nullptr) {
		delete m_ied_p;
	}
}

dx::draw::cube::cube()
{

}

dx::draw::cube::~cube()
{
	if (m_vs_p != nullptr) {
		m_vs_p->Release();
	}

	if (m_ps_p != nullptr) {
		m_ps_p->Release();
	}

	if (m_vs_blob != nullptr) {
		m_vs_blob->Release();
	}

	if (m_ps_blob != nullptr) {
		m_ps_blob->Release();
	}

	if (m_buffer_p != nullptr) {
		m_buffer_p->Release();
	}

	if (m_buffer_desc_p != nullptr) {
		delete m_buffer_desc_p;
	}
}
