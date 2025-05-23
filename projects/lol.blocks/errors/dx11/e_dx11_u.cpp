#include NAMES_INCLUDE
#include EDX11U_INCLUDE_PATH

dx11::string dx11::hr_ts(HRESULT hr) {
	_com_error err(hr);
	LPCWSTR errMsg = err.ErrorMessage();

	// make a wide temp copy
	std::wstring wide_temp(errMsg);

	// convert if necessary
#if NARROW
	std::string narrow_temp;
	{
		lb::codes code;
		narrow_temp = lb::to_narrow_string(wide_temp,&code);
		output_code(code);
	}
	return narrow_temp;
#endif

#if WIDE
	return wide_temp;
#endif
}

dx11::string dx11::debug_info_ts(ID3D11InfoQueue* debug_info_p, lol_blocks::codes* code) {
	/*

	typedef struct D3D11_MESSAGE {
	  D3D11_MESSAGE_CATEGORY Category;
	  D3D11_MESSAGE_SEVERITY Severity;
	  D3D11_MESSAGE_ID       ID;
	  const char             *pDescription;
	  SIZE_T                 DescriptionByteLength;
	} D3D11_MESSAGE;

	*/


	// Get the size of the message
	SIZE_T messageLength = 0;
	HRESULT hr = debug_info_p->GetMessage(0, NULL, &messageLength);

	// Allocate space and get the message
	D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*)malloc(messageLength);
	hr = debug_info_p->GetMessage(0, pMessage, &messageLength);

	if (pMessage == nullptr) {
		*code = lb::codes::pointer_is_nullptr;
		return {};
	}

	std::string temp(pMessage->pDescription, pMessage->DescriptionByteLength);

	// delete the memory
	if (pMessage != nullptr) {
		free(pMessage);
	}

#if NARROW

	*code = lb::codes::success;
	return temp;

#endif

#if WIDE

	std::wstring temp_wide = lb::to_wide_string(temp,code);
	return temp_wide;

#endif

}

dx11::string dx11::error_blob_ts(ID3DBlob* error, lol_blocks::codes* code) {
	if (error == nullptr) {
		*code = lb::codes::pointer_is_nullptr;
		return {};
	}

	// Get the error message from the blob
	const char* errorMessage = static_cast<const char*>(error->GetBufferPointer());
	size_t messageSize = error->GetBufferSize();

	// Convert it to a std::string
	std::string temp_error_str(errorMessage, messageSize);

	// convert if necessary
#if NARROW
	*code = lb::codes::success;
	return temp_error_str;
#endif

#if WIDE
	std::wstring wide_temp = lb::to_wide_string(temp_error_str,code);
	return wide_temp;
#endif
}

void dx11::st_vs_out(HRESULT hr,string location) {
	string dx_message = hr_ts(hr);
	string full_message = dx_message + location;
	OutputDebugString(full_message.c_str());
}