#include "draw.hpp"

testing::draw::draw(UINT window_width, UINT window_height, HWND window_handle, const string& window_name)
	:devices_11(window_width, window_height, window_handle,window_name)
{
	m_tri_p = new triangle(window_width, window_height);
	m_cube_p = new cube(window_width, window_height);
}

testing::draw::~draw()
{
	if (m_tri_p != nullptr) {
		delete m_tri_p;
	}

	if (m_cube_p != nullptr) {
		delete m_cube_p;
	}
}

errors::codes testing::draw::render_triangle(float angle)
{

	m_device_context_p->IASetInputLayout(m_tri_p->m_il_p);
	m_device_context_p->IASetVertexBuffers(0u, 1u, &m_tri_p->m_vertex_buffer_p, m_tri_p->m_stride, m_tri_p->m_offset);
	m_device_context_p->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context_p->VSSetShader(m_tri_p->m_vs_p, nullptr, 0u);
	m_device_context_p->PSSetShader(m_tri_p->m_ps_p, nullptr, 0u);

	
	m_cb.world = DirectX::XMMatrixRotationY(angle); // Rotate around Y-axis

	// Send updated matrix to the GPU
	m_device_context_p->UpdateSubresource(m_tri_p->m_constantBuffer, 0, nullptr, &m_cb, 0, 0);

	// Bind the buffer to the vertex shader at register b0
	m_device_context_p->VSSetConstantBuffers(0, 1, &m_tri_p->m_constantBuffer);

	m_device_context_p->Draw(std::size(m_tri_p->m_vertices), 0u);

	m_sc_p->Present(1u, 0);

	return errors::codes();
}

errors::codes testing::draw::render_cube()
{
	m_device_context_p->IASetInputLayout(m_cube_p->m_il_p);

	m_device_context_p->IASetVertexBuffers(0u, 1u, &m_cube_p->m_buffer_p, m_cube_p->m_stride, m_cube_p->m_offset);

	m_device_context_p->IASetIndexBuffer(m_cube_p->m_index_buffer_p, DXGI_FORMAT_R32_UINT, 0);

	m_device_context_p->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_context_p->VSSetShader(m_cube_p->m_vs_p, nullptr, 0u);

	m_device_context_p->PSSetShader(m_cube_p->m_ps_p, nullptr, 0u);

	m_device_context_p->Draw(108u, 0u);

	m_sc_p->Present(1u, 0);
	
	return errors::codes();
}

errors::codes testing::draw::clear_buffer(float red, float green, float blue)
{
	const float color[] = {
		red,green,blue,1.0f
	};
	
	m_device_context_p->ClearRenderTargetView(m_render_target_p, color);
	
	return errors::codes::success;
}

errors::codes testing::draw::ready_triangle()
{
	// get exe path
	std::filesystem::path shader_dir = std::filesystem::current_path();

	std::filesystem::path vs_path = shader_dir / "vertex_shader.hlsl";
	std::filesystem::path ps_path = shader_dir / "pixel_shader.hlsl";

	// vertex shader
	compile_shaders(vs_path, &m_tri_p->m_vs_blob,"vs_5_0");

	// pixel shader
	compile_shaders(ps_path, &m_tri_p->m_ps_blob,"ps_5_0");
	
	
	create_vertex_shader(&m_tri_p->m_vs_p, &m_tri_p->m_vs_blob);
	create_pixel_shader(&m_tri_p->m_ps_p, &m_tri_p->m_ps_blob);
	
	create_buffer(m_tri_p);
	
	return errors::codes::success;
}

errors::codes testing::draw::ready_cube()
{
	// get exe path
	std::filesystem::path shader_dir = std::filesystem::current_path();

	std::filesystem::path vs_path = shader_dir / "vertex_shader.hlsl";
	std::filesystem::path ps_path = shader_dir / "pixel_shader.hlsl";

	// vertex shader
	compile_shaders(vs_path, &m_cube_p->m_vs_blob, "vs_5_0");

	// pixel shader
	compile_shaders(ps_path, &m_cube_p->m_ps_blob, "ps_5_0");


	create_vertex_shader(&m_cube_p->m_vs_p, &m_cube_p->m_vs_blob);
	create_pixel_shader(&m_cube_p->m_ps_p, &m_cube_p->m_ps_blob);
	create_buffer(m_cube_p);

	return errors::codes::success;
}

// TODO: finish this
errors::codes testing::draw::create_buffer(triangle* tri_p)
{
#if ENABLE_FULL_DEBUG

	if (tri_p == nullptr) {
		errors::handle_basic_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (tri_p == nullptr) {
		code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
		throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif

	D3D11_BUFFER_DESC cbd = {};
	cbd.Usage = D3D11_USAGE_DEFAULT;     // GPU updates it, CPU can modify it
	cbd.ByteWidth = sizeof(ConstantBuffer); // Size of our struct
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Used as a constant buffer

	m_device_p->CreateBuffer(&cbd, nullptr, &tri_p->m_constantBuffer);




	{
		HRESULT hr;
		hr = m_device_p->CreateBuffer(tri_p->m_vertex_buffer_desc_p, tri_p->m_vertex_sub_data_p, &tri_p->m_vertex_buffer_p);
		if (FAILED(hr)) {
#if ENABLE_FULL_DEBUG
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				errors::dx_error err(error, hr);
				errors::show_error_message_window(err.full_error_message());
			}
#endif

#if ENABLE_ALL_EXCEPTIONS
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				throw errors::dx_error(error, hr);
			}
#endif
		}
	}


	

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
		HRESULT hr;
		hr = m_device_p->CreateInputLayout(
			tri_p->m_ied_p,
			2u, // this is how many desc are in the m_ied_p array
			tri_p->m_vs_blob->GetBufferPointer(),
			tri_p->m_vs_blob->GetBufferSize(),
			&tri_p->m_il_p
		);

		if (FAILED(hr)) {
#if ENABLE_FULL_DEBUG
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				errors::dx_error err(error, hr);
				errors::show_error_message_window(err.full_error_message());
			}
#endif

#if ENABLE_ALL_EXCEPTIONS
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				throw errors::dx_error(error, hr);
			}
#endif
		}
	}

	m_device_context_p->OMSetRenderTargets(1u, &m_render_target_p, nullptr);

	m_device_context_p->RSSetViewports(1u, tri_p->m_view_desc_p);

	return errors::codes::success;
}

errors::codes testing::draw::create_buffer(cube* cube_p)
{

#if ENABLE_FULL_DEBUG

	if (cube_p == nullptr) {
		errors::handle_basic_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif

#if ENABLE_ALL_EXCEPTIONS

	if (cube_p == nullptr) {
		code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
		throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif



	{
		HRESULT hr;
		hr = m_device_p->CreateBuffer(cube_p->m_buffer_desc_p, cube_p->m_sub_data_p, &cube_p->m_buffer_p);
		if (FAILED(hr)) {
#if ENABLE_FULL_DEBUG
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				errors::dx_error err(error, hr);
				errors::show_error_message_window(err.full_error_message());
			}
#endif

#if ENABLE_ALL_EXCEPTIONS
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				throw errors::dx_error(error, hr);
			}
#endif
		}
	}

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
		HRESULT hr;
		hr = m_device_p->CreateInputLayout(
			cube_p->m_ied_p,
			1u, // this is how many desc are in the m_ied_p array
			cube_p->m_vs_blob->GetBufferPointer(),
			cube_p->m_vs_blob->GetBufferSize(),
			&cube_p->m_il_p
		);

		if (FAILED(hr)) {
#if ENABLE_FULL_DEBUG
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				errors::dx_error err(error, hr);
				errors::show_error_message_window(err.full_error_message());
			}
#endif

#if ENABLE_ALL_EXCEPTIONS
			{
				code_error_objs::code_obj error(code_error_objs::dx_error);
				throw errors::dx_error(error, hr);
			}
#endif
		}
	}

	m_device_context_p->OMSetRenderTargets(1u, &m_render_target_p, nullptr);

	m_device_context_p->RSSetViewports(1u, cube_p->m_view_desc_p);

	return errors::codes::success;
}

errors::codes testing::draw::create_vertex_shader(ID3D11VertexShader** vs_pp, ID3DBlob** vs_blob_pp)
{

#if ENABLE_FULL_DEBUG
	
	/*
	* vertex shader pointer gets created in this function
	* so no checks needed here
	if (vs_p == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}
	*/

	if (vs_blob_pp == nullptr) {
		errors::handle_basic_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS
	
	/*
	* vertex shader pointer gets created in this function
	* so no checks needed here
	if (vs_p == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3D11VertexShader* vs_p"));
	}
	*/

	if (vs_blob_pp == nullptr) {
		code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
		throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("ID3DBlob** vs_blob_pp"));
	}

#endif
	
	auto vs_blob_p = *(vs_blob_pp);
	
	HRESULT hr;
	
	hr = m_device_p->CreateVertexShader(
		vs_blob_p->GetBufferPointer(),
		vs_blob_p->GetBufferSize(),
		nullptr,
		vs_pp
	);
	


#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		errors::dx_error create_vs_error(error,hr);
		errors::show_error_message_window(create_vs_error.full_error_message());
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		throw errors::dx_error(error, hr);
	}

#endif
	
	// the case where both exceptions and debug are disabled
	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}

	return errors::codes::success;
}

errors::codes testing::draw::create_pixel_shader(ID3D11PixelShader** ps_pp, ID3DBlob** ps_blob_pp)
{

#if ENABLE_FULL_DEBUG
	
	/*
	* pixel shader is created in this function
	* so no checks needed here
	if (ps_p == nullptr) {
		errors::handle_error_codes(errors::codes::pointer_is_nullptr);
	}
	*/

	if (ps_blob_pp == nullptr) {
		errors::handle_basic_error_codes(errors::codes::pointer_is_nullptr);
	}

#endif


#if ENABLE_ALL_EXCEPTIONS
	
	/*
	* pixel shader is created in this function 
	* so no checks needed here
	if (ps_p == nullptr) {
		throw errors::pointer_is_nullptr(READ_ONLY_STRING("ID3D11VertexShader* vs_p"));
	}
	*/

	if (ps_blob_pp == nullptr) {
		code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
		throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("ID3DBlob* vs_blob"));
	}

#endif

	auto ps_blob_p = *(ps_blob_pp);

	HRESULT hr;

	hr = m_device_p->CreatePixelShader(
		ps_blob_p->GetBufferPointer(),
		ps_blob_p->GetBufferSize(),
		nullptr,
		ps_pp
	);

#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		errors::dx_error create_ps_error(error,hr);
		errors::show_error_message_window(create_ps_error.full_error_message());
	}

#endif


#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		throw errors::dx_error(error,hr);
	}

#endif



	// the case where both exceptions and debug are disabled
	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}

	return errors::codes::success;
}

errors::codes testing::draw::compile_shaders(std::filesystem::path shader_fp, ID3DBlob** shader_blob_pp, LPCSTR target_profile)
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
	
	ID3DBlob* error_blob_p = nullptr;

	HRESULT hr;
	
	// Compile Vertex Shader
	hr = D3DCompileFromFile(
		shader_fp.c_str(),										// Filename
		nullptr,												// Optional macros
		nullptr,												// Optional include handler
		"main",													// Entry point
		target_profile,											// Target profile
		
#if ENABLE_DX_DEBUG
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,		// Flags
#else
		D3DCOMPILE_OPTIMIZATION_LEVEL3,
#endif
		
		0,														// Additional flags
		shader_blob_pp,											// Compiled shader
		&error_blob_p											// Errors
	);
	
#if ENABLE_FULL_DEBUG

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		errors::dx_error err(error, hr, error_blob_p);
		errors::show_error_message_window(err.full_error_message());
	}

	if (error_blob_p != nullptr) {
		error_blob_p->Release();
	}

#endif

#if ENABLE_ALL_EXCEPTIONS

	if (FAILED(hr)) {
		code_error_objs::code_obj error(code_error_objs::dx_error);
		throw errors::dx_error(error, hr);
	}

	if (error_blob_p != nullptr) {
		error_blob_p->Release();
	}

#endif

	if (error_blob_p != nullptr) {
		error_blob_p->Release();
	}


	if (FAILED(hr)) {
		return errors::codes::dx_error;
	}
	return errors::codes::success;
}

testing::draw::triangle::triangle(UINT window_width, UINT window_height)
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

	m_vertex_buffer_desc_p = new D3D11_BUFFER_DESC{
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


	m_vertex_sub_data_p = new D3D11_SUBRESOURCE_DATA{
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

	m_ied_p = new D3D11_INPUT_ELEMENT_DESC[]{
		{
			"POSITION", 
			0u,
			DXGI_FORMAT_R32G32_FLOAT,
			0u,
			0u,
			D3D11_INPUT_PER_VERTEX_DATA,
			0u
		},

		{
			"COLOR",
			0u,
			DXGI_FORMAT_R32G32_FLOAT,
			0u,
			8u,
			D3D11_INPUT_PER_VERTEX_DATA,
			0u
		}
	};
}

testing::draw::triangle::~triangle()
{
	// vertex shader pointer
	if (m_vs_p != nullptr) {
		m_vs_p->Release();
	}

	// pixel shader pointer
	if (m_ps_p != nullptr) {
		m_ps_p->Release();
	}

	// vertex shader blob data
	// compiled vertex shader code
	if (m_vs_blob != nullptr) {
		m_vs_blob->Release();
	}

	// pixel shader blob data
	// compiled pixel shader code
	if (m_ps_blob != nullptr) {
		m_ps_blob->Release();
	}

	// vertex buffer pointer
	if (m_vertex_buffer_p != nullptr) {
		m_vertex_buffer_p->Release();
	}

	// vertex buffer description pointer
	if (m_vertex_buffer_desc_p != nullptr) {
		delete m_vertex_buffer_desc_p;
	}

	// subresource data pointer
	// 
	if (m_vertex_sub_data_p != nullptr) {
		delete m_vertex_sub_data_p;
	}

	if (m_stride != nullptr) {
		delete m_stride;
	}

	if (m_offset != nullptr) {
		delete m_offset;
	}

	if (m_il_p != nullptr) {
		m_il_p->Release();
	}

	if (m_ied_p != nullptr) {
		delete[] m_ied_p;
	}

	if (m_constantBuffer != nullptr) {
		m_constantBuffer->Release();
	}
}

testing::draw::cube::cube(UINT window_width, UINT window_height)
{
	m_vertices = new vertex[]{
		// Front face
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },

		// Back face
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },

		// Left face
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },

		// Right face
		{  0.5f, -0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },

		// Top face
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f, -0.5f },

		// Bottom face
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f,  0.5f },
	};

	m_indices = new UINT[]{
		// Front face
		0, 1, 2, 0, 2, 3,
		// Back face
		4, 5, 6, 4, 6, 7,
		// Left face
		8, 9, 10, 8, 10, 11,
		// Right face
		12, 13, 14, 12, 14, 15,
		// Top face
		16, 17, 18, 16, 18, 19,
		// Bottom face
		20, 21, 22, 20, 22, 23
	};

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

	m_ied_p = new D3D11_INPUT_ELEMENT_DESC[]{
		{
			"Position",
			0u,
			DXGI_FORMAT_R32G32_FLOAT,
			0u,
			0u,
			D3D11_INPUT_PER_VERTEX_DATA,
			0u
		}


	};
}

testing::draw::cube::~cube()
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

	if (m_il_p != nullptr) {
		m_il_p->Release();
	}

	if (m_ied_p != nullptr) {
		delete[] m_ied_p;
	}

	if (m_vertices != nullptr) {
		delete[] m_vertices;
	}

	if (m_indices != nullptr) {
		delete[] m_indices;
	}

	if (m_index_buffer_p != nullptr) {
		m_index_buffer_p->Release();
	}
}
