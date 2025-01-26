#include "draw.hpp"

dx::draw::draw(UINT window_width, UINT window_height, HWND window_handle, const string& window_name)
	:devices_11(window_width, window_height, window_handle,window_name)
{

}

dx::draw::~draw()
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
}

errors::codes dx::draw::clear_buffer(float red, float green, float blue)
{
	const float color[] = {
		red,green,blue,1.0f
	};
	
	m_device_context_p->ClearRenderTargetView(m_render_target_p, color);
	
	return errors::codes::success;
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
	
	
	
	return errors::codes();
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
